// Fill out your copyright notice in the Description page of Project Settings.


#include "EnviromentStats.h"
#include "Engine/World.h"
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

float UEnviromentStats::CalculateLightReceived(AActor * Actor)
{
	AActor* Owner = GetOwner();
	if (Owner)
	{
		float LightReceived = 0;
		TArray<ACustomLight*> OverlappingLights = GetOverlappingLights(Owner);

		if (OverlappingLights.Num() > 0)
		{
			for (ACustomLight* Light : OverlappingLights)
			{
				LightReceived += CalculateLightApplied(Owner, Light);
			}

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
		ECollisionChannel CollisionChannel = ECollisionChannel::ECC_WorldDynamic;

		if (World->LineTraceSingleByChannel(HitResult, StartPos, EndPos, CollisionChannel))
		{
			if (HitResult.GetActor() == Target)
			{
				float DistanceMultiplier = FMath::GetMappedRangeValueClamped(FVector2D(0, Light->PointLight->AttenuationRadius), FVector2D(1, 0), HitResult.Distance);
				DistanceMultiplier *= Light->PointLight->Intensity / 1000;

				float Result = 0;
				float LightRadius = Light->PointLight->AttenuationRadius;

				if (HitResult.Distance <= LightRadius)
				{
					Result = FMath::Pow(1.0 - (HitResult.Distance / LightRadius), ((Light->PointLight->LightFalloffExponent + 1) * (LightRadius * 1.25)*0.0001));
					
				}
				else
				{
					Result = 0.0f;
				}

				return Result;
			}
		}
	}

	return 0.0f;
}

