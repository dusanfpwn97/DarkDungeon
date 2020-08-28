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

	// ...
	
}

// Calculate the sum of the light received from all colliding lights
float UEnviromentStats::CalculateLightReceived(AActor * Actor)
{
	if (Actor)
	{
		float LightReceived = 0;
		TArray<ACustomLight*> OverlappingLights = GetOverlappingLights(Actor);

		if (OverlappingLights.Num() > 0)
		{
			for (ACustomLight* Light : OverlappingLights)
			{
				// Sum each individual light
				LightReceived += CalculateLightApplied(Actor, Light);
			}
			LastLightReceived = LightReceived;

			OnCalculationForLightCalled(LightReceived);
			return LightReceived;
		}
	}

	return 0.f;
}

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

float UEnviromentStats::CalculateLightApplied(AActor* Target, ACustomLight* Light)
{
	UWorld* World = GetWorld();

	if (Target && Light && World)
	{
		float LightApplied = 0;

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

				if (HitResult.Distance <= LightRadius)
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

