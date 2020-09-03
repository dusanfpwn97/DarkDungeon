// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.


#include "ACFMountComponent.h"
#include "ACFRiderComponent.h"
#include "Actors/ACFCharacter.h"
#include "Components/ACFActionsManagerComponent.h"
#include "Game/ACFFunctionLibrary.h"
#include "Game/ACFPlayerController.h"
#include "ACFAnimationPointComponent.h"
#include "AI/Components/ACFCompanionGroupAIComponent.h"
#include <Components/SkinnedMeshComponent.h>
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UACFMountComponent::UACFMountComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
	// ...
}


// Called when the game starts
void UACFMountComponent::BeginPlay()
{
	Super::BeginPlay();
	
	if (GetCharacterOwner()) {
		UACFActionsManagerComponent* actionsComp = GetCharacterOwner()->FindComponentByClass<UACFActionsManagerComponent>();
		if (actionsComp) {
			actionsComp->OnActionTriggered.AddDynamic(this, &UACFMountComponent::HandleActionTriggered);
		}
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Mount must be Characters! - UACFMountComponent::BeginPlay"));
	}
}


void UACFMountComponent::StartMount(ACharacter* inRider)
{
	if (!bIsMounted && inRider) {
		
		UACFRiderComponent* riderComp = inRider->FindComponentByClass<UACFRiderComponent>();
		if (riderComp) {

			riderComp->StartMount(this);
		}		
	}
}



void UACFMountComponent::StopMount(const FName& dismountPoint /*= NAME_None*/)
{
	if (rider) {
		UACFRiderComponent* riderComp = rider->FindComponentByClass<UACFRiderComponent>();
		if (riderComp) {

			riderComp->StartDismount(dismountPoint);
		}
	}
}

FTransform UACFMountComponent::GetMountPointTransform() const
{	
	if (GetCharacterOwner() && GetCharacterOwner()->GetMesh()) {
		return GetCharacterOwner()->GetMesh()->GetSocketTransform(MountPointSocket);
	}
	UE_LOG(LogTemp, Error, TEXT("Invalid Mount Point ! - UACFMountComponent::GetMountPointTransform"))
	return FTransform();
}


class UACFAnimationPointComponent* UACFMountComponent::GetDismountPoint(const FName& dismountPoint /*= NAME_None*/) const
{
	TArray<UACFAnimationPointComponent*> executionPoints;
	FName actualDismount = dismountPoint == NAME_None ? DefaultDismountPoint : dismountPoint;
	GetOwner()->GetComponents<UACFAnimationPointComponent>(executionPoints);
	for (const auto execPoint : executionPoints) {
		if (execPoint->GetPointTag() == actualDismount) {
			return execPoint;
		}
	}
	return nullptr;
}

void UACFMountComponent::HandleActionTriggered(FGameplayTag ActionState, EActionPriority Priority)
{
	if (rider && ActionsToBeRetriggeredToRider.Contains(ActionState)) {
		UACFActionsManagerComponent* actionsComp = rider->FindComponentByClass<UACFActionsManagerComponent>();
		if (actionsComp) {
			actionsComp->TriggerAction(ActionState, Priority);
		}
	}
}

void UACFMountComponent::OnRep_IsMounted()
{
	OnMountedStateChanged.Broadcast(bIsMounted);
}

void UACFMountComponent::SetMounted(bool inMounted)
{
	bIsMounted = inMounted;
	if (!bIsMounted) {
		rider = nullptr;
	}
	if (bIsPlayerCompanion) {
		AACFPlayerController* playerContr = UACFFunctionLibrary::GetLocalACFPlayerController(this);

		if (playerContr) {
			if (bIsMounted) {
				playerContr->GetCompanionsComponent()->RemoveAgentFromGroup(Cast<AACFCharacter>(GetCharacterOwner()));
			}
			else {

				playerContr->GetCompanionsComponent()->AddExistingCharacterToGroup(Cast<AACFCharacter>(GetCharacterOwner()));
			}
		}
	}
				
	OnMountedStateChanged.Broadcast(inMounted);
}

void UACFMountComponent::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UACFMountComponent, bIsMounted);
}