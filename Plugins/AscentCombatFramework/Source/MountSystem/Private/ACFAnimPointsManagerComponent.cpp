// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.


#include "ACFAnimPointsManagerComponent.h"
#include "ACFAnimationPointComponent.h"
#include <GameFramework/Character.h>

// Sets default values for this component's properties
UACFAnimPointsManagerComponent::UACFAnimPointsManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UACFAnimPointsManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	characterOwner = Cast<ACharacter>(GetOwner());
	
}



FName UACFAnimPointsManagerComponent::GetNearestAnimationPointTag(const FVector& location) const
{
	UACFAnimationPointComponent* executionPoint = GetNearestAnimationPoint(location);
	if (executionPoint) {
		return executionPoint->GetPointTag();
	}

	return NAME_None;
}

class UACFAnimationPointComponent* UACFAnimPointsManagerComponent::GetNearestAnimationPoint(const FVector& location) const
{
	TArray<UACFAnimationPointComponent*> executionPoints;
	GetOwner()->GetComponents<UACFAnimationPointComponent>(executionPoints);

	UACFAnimationPointComponent* toBeReturned = nullptr;
	float minDistance = BIG_NUMBER;

	for (const auto execPoint : executionPoints) {
		FVector componentLoc = execPoint->GetComponentLocation();
		FVector distanceV = location - componentLoc;
		float distance; 
		distanceV.ToDirectionAndLength(distanceV, distance);
		if (distance < minDistance) {
			toBeReturned = execPoint;
			minDistance = distance;
		}
	}

	return toBeReturned;
}
