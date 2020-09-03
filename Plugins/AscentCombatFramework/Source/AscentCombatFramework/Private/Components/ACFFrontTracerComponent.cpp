// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.


#include "Components/ACFFrontTracerComponent.h"
#include <Kismet/KismetSystemLibrary.h>
#include <Components/ActorComponent.h>
#include <GameFramework/Actor.h>
#include <CollisionQueryParams.h>
#include "Game/ACFFunctionLibrary.h"
#include "Actors/ACFCharacter.h"

// Sets default values for this component's properties
UACFFrontTracerComponent::UACFFrontTracerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	SetComponentTickEnabled(false);

}


// Called when the game starts
void UACFFrontTracerComponent::BeginPlay()
{
	Super::BeginPlay();

	SetComponentTickEnabled(false);	
}


// Called every frame
void UACFFrontTracerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector start = GetComponentLocation();
	FVector end = start + (GetOwner()->GetActorForwardVector() * TraceLength);

	TArray<AActor*> actorsToIgnore;
	actorsToIgnore.Add(UACFFunctionLibrary::GetLocalACFPlayerCharacter(this));

	EDrawDebugTrace::Type debugType = bShowDebugTrace ? EDrawDebugTrace::Type::ForOneFrame : EDrawDebugTrace::Type::None;

	FHitResult outResult;

	if (UKismetSystemLibrary::LineTraceSingleForObjects(this, start, end, ChannelsToTrace, false, actorsToIgnore, debugType, outResult, true)) {
		if (outResult.Actor->IsValidLowLevel() && outResult.Actor->GetClass()->IsChildOf(ActorToFind) &&
			outResult.Actor != currentTracedActor) {
			SetCurrentTracedActor(outResult.Actor.Get());
		}
	}
	else if(currentTracedActor){
		SetCurrentTracedActor(nullptr);
	}
}

void UACFFrontTracerComponent::StartContinuousTrace()
{
	if (ActorToFind) {
		SetComponentTickEnabled(true);
	}
}

void UACFFrontTracerComponent::StopContinuousTrace()
{
	SetComponentTickEnabled(false);
	SetCurrentTracedActor(nullptr);
}

void UACFFrontTracerComponent::SetCurrentTracedActor(AActor* newActor)
{
	currentTracedActor = newActor;
	OnNewActorDetected.Broadcast(currentTracedActor);
}

