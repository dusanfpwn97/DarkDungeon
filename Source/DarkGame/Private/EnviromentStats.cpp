// Fill out your copyright notice in the Description page of Project Settings.


#include "EnviromentStats.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "..\Public\EnviromentStats.h"

// Sets default values for this component's properties
UEnviromentStats::UEnviromentStats()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// Called when the game starts
void UEnviromentStats::BeginPlay()
{
	Super::BeginPlay();

	// Should start calculating on Begin Play? This bool can be check on or off in the component
	if (ShouldCalculateLightReceived)
	{
		StartCalculatingLightReceived();
	}
}

// Calculate the sum of the light received from all colliding lights
void UEnviromentStats::CalculateLightReceived()
{
	// Gets the actor that this component is attached to
	AActor* Owner = GetOwner();

	if (Owner)
	{
		float TempLightReceivedSum = 0;
		TArray<ACustomLight*> OverlappingLights = GetOverlappingLights(Owner);

		if (OverlappingLights.Num() > 0)
		{
			for (ACustomLight* Light : OverlappingLights)
			{
				// Sum intensity for each overlapping light
				TempLightReceivedSum += CalculateLightApplied(Owner, Light);
			}

			LastReceivedLightIntensity = TempLightReceivedSum;
		}
		else
		{
			LastReceivedLightIntensity = 0;
		}
	}
}

// Get all of the CustomLights that overlap the target actor
TArray<ACustomLight*> UEnviromentStats::GetOverlappingLights(AActor* Target)
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
void UEnviromentStats::StartCalculatingLightReceived()
{
	ShouldCalculateLightReceived = true;

	UWorld* World = GetWorld();
	if (World)
	{
		GetWorld()->GetTimerManager().SetTimer(CalculateLightReceivedTimerHandle, this, &UEnviromentStats::CalculateLightReceived, UpdateTimeCalculateLightReceived, true);
	}
}

// Calculate light applied to the Target Actor By a given light
float UEnviromentStats::CalculateLightApplied(AActor* Target, ACustomLight* Light)
{
	UWorld* World = GetWorld();

	if (Target && Light && World)
	{
		float LightApplied = 0;

		// Setup LineTrace (RayTrace)
		FHitResult HitResult;
		FVector StartPos = Light->GetActorLocation();
		FVector EndPos	 = Target->GetActorLocation();
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

			
				if (HitResult.Distance <= LightRadius && LightVisible==true)
				{
					Result = FMath::Pow(1 - (HitResult.Distance / LightRadius), ((Light->PointLight->LightFalloffExponent*2 + 1) * (LightRadius * 1.25)*0.0001));
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
void UEnviromentStats::StopCalculatingLightReceived()
{
	if (CalculateLightReceivedTimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(CalculateLightReceivedTimerHandle);
		ShouldCalculateLightReceived = false;
	}
}

// Get the last calculated Received Light Intensity. If the timer is not active, calculate it and start the timer
float UEnviromentStats::GetLastReceivedLightIntensity()
{
	if (!ShouldCalculateLightReceived)
	{
		CalculateLightReceived();
		StartCalculatingLightReceived();
	}
	return LastReceivedLightIntensity;
}

