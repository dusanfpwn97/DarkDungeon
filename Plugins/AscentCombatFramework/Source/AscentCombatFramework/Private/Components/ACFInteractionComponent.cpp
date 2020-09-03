// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#include "Components/ACFInteractionComponent.h"
#include "Interfaces/ACFInteractableInterface.h"
#include <GameFramework/Actor.h>

// Sets default values for this component's properties
UACFInteractionComponent::UACFInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	SetCollisionResponseToAllChannels(ECR_Ignore);
	SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CollisionChannels.Add(ECollisionChannel::ECC_Pawn);
	SetComponentTickEnabled(false);
}



// Called when the game starts
void UACFInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	PawnOwner = Cast<APawn>(GetOwner());
	OnComponentBeginOverlap.AddDynamic(this, &UACFInteractionComponent::OnActorEnteredDetector);
	OnComponentEndOverlap.AddDynamic(this, &UACFInteractionComponent::OnActorLeavedDetector);

	if (!PawnOwner)
	{
		UE_LOG(LogTemp, Error, TEXT("UACFInteractionComponent is Not in a pawn!"));
	}

	if(bAutoEnableOnBeginPlay)
		EnableDetection(bAutoEnableOnBeginPlay);


}

void UACFInteractionComponent::EnableDetection(bool bIsEnabled)
{
	if (bIsEnabled)
	{
		InitChannels();
		SetSphereRadius(0.f, false);
		SetSphereRadius(InteractableArea, true);
		SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
	else
	{
		SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void UACFInteractionComponent::Interact_Implementation()
{
	if (currentBestInteractableActor)
	{
		bool bImplements = currentBestInteractableActor->GetClass()->ImplementsInterface(UACFInteractableInterface::StaticClass());
		if (bImplements)
		{
			IACFInteractableInterface::Execute_OnInteractedByPawn(currentBestInteractableActor, PawnOwner);
		}
		
	}
	
}

bool UACFInteractionComponent::Interact_Validate()
{
	return true;
}


void UACFInteractionComponent::UpdateInteractionArea()
{
	//SetSphereRadius(0.f);
	SetSphereRadius(InteractableArea, true);
}

void UACFInteractionComponent::SetCurrentBestInteractable(class AActor* actor)
{
	if (currentBestInteractableActor)
	{
		bool bImplements = currentBestInteractableActor->GetClass()->ImplementsInterface(UACFInteractableInterface::StaticClass());
		if (bImplements)
		{
			IACFInteractableInterface::Execute_OnInteractableUnregisteredByPawn(currentBestInteractableActor, PawnOwner);
		}
	}

	if (actor)
	{
		currentBestInteractableActor = actor;
		bool bImplements = currentBestInteractableActor->GetClass()->ImplementsInterface(UACFInteractableInterface::StaticClass());
		if (bImplements)
		{
			IACFInteractableInterface::Execute_OnInteractableRegisteredByPawn(currentBestInteractableActor, PawnOwner);
		}		
	}
	else
	{
		currentBestInteractableActor = nullptr;
	}
	OnInteractableRegistered.Broadcast(actor);
}

void UACFInteractionComponent::OnActorEnteredDetector(UPrimitiveComponent * _overlappedComponent, AActor * _otherActor, UPrimitiveComponent * _otherComp, int32 _otherBodyIndex, bool _bFromSweep, const FHitResult & _SweepResult)
{
	bool bImplements = _otherActor->GetClass()->ImplementsInterface(UACFInteractableInterface::StaticClass());
	if (bImplements && PawnOwner && _otherActor != PawnOwner && IACFInteractableInterface::Execute_CanBeInteracted(_otherActor, PawnOwner))
	{
		interactables.AddUnique(_otherActor);
		SetComponentTickEnabled(true);
	}
}

void UACFInteractionComponent::OnActorLeavedDetector(UPrimitiveComponent * _overlappedComponent, AActor * _otherActor, UPrimitiveComponent * _otherComp, int32 _otherBodyIndex)
{
	if (interactables.Contains(_otherActor))
		interactables.Remove(_otherActor);

	if (currentBestInteractableActor && currentBestInteractableActor == _otherActor)
	{
		SetCurrentBestInteractable(nullptr);	
	}
}

void UACFInteractionComponent::RefreshInteractions()
{
	if (interactables.Num() == 0)
	{
		SetComponentTickEnabled(false);
		return;
	}
	SetComponentTickEnabled(true);

	for (auto interactable : interactables)
	{
		if (currentBestInteractableActor)
		{
			if (interactable && PawnOwner->GetDistanceTo(interactable) < PawnOwner->GetDistanceTo(currentBestInteractableActor))
				SetCurrentBestInteractable(interactable);		
		}
		else
		{
			SetCurrentBestInteractable(interactable);
		}
			
	}
}

// Called every frame
void UACFInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	RefreshInteractions();
}

void UACFInteractionComponent::AddCollisionChannel(TEnumAsByte<ECollisionChannel> inTraceChannel)
{
	if (!CollisionChannels.Contains(inTraceChannel))
	{
		CollisionChannels.Add(inTraceChannel);
		InitChannels();
	}
}

void UACFInteractionComponent::RemoveCollisionChannel(TEnumAsByte<ECollisionChannel> inTraceChannel)
{
	if (CollisionChannels.Contains(inTraceChannel))
	{
		CollisionChannels.Remove(inTraceChannel);
		InitChannels();
	}
}


void UACFInteractionComponent::InitChannels()
{
	SetCollisionResponseToAllChannels(ECR_Ignore);
	SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	for (auto channel : CollisionChannels)
	{
		SetCollisionResponseToChannel(channel, ECR_Overlap);
	}
}