// Fill out your copyright notice in the Description page of Project Settings.


#include "CharBase.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

// Sets default values
ACharBase::ACharBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
//	SetIsReplicated(true);
	bReplicates = true;
	
	bNetUseOwnerRelevancy = true;
}

void ACharBase::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ACharBase, LastReceivedLightIntensity);
	DOREPLIFETIME(ACharBase, AdditionalLightIntensity);
}

void ACharBase::ServerChangeAdditionalLightIntensity_Implementation(float NewAdditinalLightIntensity)
{
	AdditionalLightIntensity = NewAdditinalLightIntensity;
}

// Called when the game starts or when spawned
void ACharBase::BeginPlay()
{
	Super::BeginPlay();

	// Should start calculating on Begin Play? This bool can be check on or off in the component
	if (ShouldCalculateLightReceived && GetLocalRole() == ENetRole::ROLE_Authority)
	{
		ServerStartCalculatingLightReceived();
	}
}

// Called every frame
void ACharBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


// Called to bind functionality to input
void ACharBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

/*

// Calculate the sum of the light received from all colliding lights
void ACharBase::ServerCalculateLightReceived()
{


}*/
void ACharBase::ServerCalculateLightReceived_Implementation()
{
	// Gets the actor that this component is attached to
	AActor* ActorToCalculateFor = this;

	if (ActorToCalculateFor)
	{
		float TempLightReceivedSum = 0;
		TArray<ACustomLight*> OverlappingLights = ServerGetOverlappingLights(ActorToCalculateFor);

		if (OverlappingLights.Num() > 0)
		{
			for (ACustomLight* Light : OverlappingLights)
			{
				// Sum intensity for each overlapping light
				TempLightReceivedSum += CalculateLightApplied(ActorToCalculateFor, Light);
			}

			LastReceivedLightIntensity = TempLightReceivedSum + AdditionalLightIntensity;
		}
		else
		{
			LastReceivedLightIntensity = 0;
		}
	}
}

// Get all of the CustomLights that overlap the target actor
TArray<ACustomLight*> ACharBase::ServerGetOverlappingLights(AActor* Target)
{
	TArray<AActor*> OverlappingActors;
	Target->GetOverlappingActors(OverlappingActors, TSubclassOf<ACustomLight>());

	TArray<ACustomLight*> OverlappingLights;
	if (OverlappingActors.Num() > 0)
	{
		for (AActor* OverlappingActor : OverlappingActors)
		{
			OverlappingLights.Add(Cast<ACustomLight>(OverlappingActor));
		}
	}

	return OverlappingLights;
}

// Starts the timer for calculating the light received
void ACharBase::ServerStartCalculatingLightReceived()
{
	ShouldCalculateLightReceived = true;

	UWorld* World = GetWorld();
	if (World)
	{
		GetWorld()->GetTimerManager().SetTimer(CalculateLightReceivedTimerHandle, this, &ACharBase::ServerCalculateLightReceived, UpdateTimeCalculateLightReceived, true);
	}
}

// Calculate light applied to the Target Actor By a given light
float ACharBase::CalculateLightApplied(AActor* Target, ACustomLight* Light)
{
	UWorld* World = GetWorld();

	if (Target && Light && World)
	{
		float LightApplied = 0;

		// Setup LineTrace (RayTrace)
		FHitResult HitResult;
		FVector StartPos = Light->GetActorLocation();
		FVector EndPos = Target->GetActorLocation();
		ECollisionChannel CollisionChannel = ECollisionChannel::ECC_GameTraceChannel1;

		if (World->LineTraceSingleByChannel(HitResult, StartPos, EndPos, CollisionChannel))
		{
			if (ShouldVisualizeLightReceivedTrace)
			{
				DrawDebugLine(World, StartPos, HitResult.Location, FColor(255, 228, 100), false, -1, 0, 1);
			}

			if (HitResult.GetActor() == Target)
			{
				float Result = 0;
				float LightRadius = Light->PointLight->AttenuationRadius;
				bool LightVisible = Light->PointLight->IsVisible(); //gs 09 01 20

				if (HitResult.Distance <= LightRadius && LightVisible == true)
				{
					Result = Light->LightAppliedMultiplier * Light->PointLight->Intensity * 0.001 * FMath::Pow(1 - (HitResult.Distance / LightRadius), ((Light->PointLight->LightFalloffExponent * 2 + 1) * (LightRadius * 1.25)*0.0001));
				}
				else
				{
					Result = 0.0f;
				}
				//
				return Result;
			}
		}
	}

	return 0.0f;
}

// Stops the timer for calculating the Light received
void ACharBase::ServerStopCalculatingLightReceived()
{
	if (CalculateLightReceivedTimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(CalculateLightReceivedTimerHandle);
		ShouldCalculateLightReceived = false;
	}
}

// Get the last calculated Received Light Intensity. If the timer is not active, calculate it and start the timer
float ACharBase::GetLastReceivedLightIntensity()
{
	if (!ShouldCalculateLightReceived)
	{
		ServerCalculateLightReceived();
		ServerStartCalculatingLightReceived();
	}
	return LastReceivedLightIntensity;
}