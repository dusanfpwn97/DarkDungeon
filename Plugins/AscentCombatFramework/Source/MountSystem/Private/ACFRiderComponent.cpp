// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.


#include "ACFRiderComponent.h"
#include <GameFramework/Character.h>
#include "CASSnapperComponent.h"
#include "ACFMountComponent.h"
#include <Components/CapsuleComponent.h>
#include <Components/SkeletalMeshComponent.h>
#include <GameFramework/PlayerController.h>
#include <TimerManager.h>
#include "ACFAnimationPointComponent.h"
#include "Animation/ACFAnimInstance.h"
#include <GameFramework/CharacterMovementComponent.h>
#include "Net/UnrealNetwork.h"


// Sets default values for this component's properties
UACFRiderComponent::UACFRiderComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
	// ...
}


// Called when the game starts
void UACFRiderComponent::BeginPlay()
{
	Super::BeginPlay();

	charOwner = Cast<ACharacter>(GetOwner());
	
}

void UACFRiderComponent::StartMount_Implementation(UACFMountComponent* mount)
{
	if (bIsSnapping) {
		return;
	}

	if (mount && mount->CanBeMounted() && charOwner) {
		Mount = mount;
		Internal_Ride(true);
		FinishMount();
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Impossible to Mount!"));
	}
}

bool UACFRiderComponent::StartMount_Validate(UACFMountComponent* mount) {
	return true;
}


void UACFRiderComponent::HandleSnapPointReached(bool bSuccess){
	bIsSnapping = false;
	UCASSnapperComponent* snapComp = charOwner->FindComponentByClass<UCASSnapperComponent>();
	if (snapComp) {
		snapComp->OnSnapPointReached.RemoveDynamic(this, &UACFRiderComponent::HandleSnapPointReached);
	}
	if (bSuccess) {
		FinishMount();
	}
	else {
		StartDismount();
	}
}

  
void UACFRiderComponent::OnRep_IsRiding()
{
	OnRidingStateChanged.Broadcast(bIsRiding);
}

void UACFRiderComponent::StartDismount_Implementation(const FName& dismountPoint /*= NAME_None*/){
	  if (!bIsRiding) {
		  return;
	  }
	  FinishDismount(dismountPoint);
}

bool UACFRiderComponent::StartDismount_Validate(const FName& dismountPoint /*= NAME_None*/){
	return true;
}

void UACFRiderComponent::FinishMount(){
	AController* contr = charOwner->GetController();
	ACharacter* mountedChar = Cast< ACharacter>(Mount->GetOwner());
	if (contr && bPossessMount) {
		mountedChar->DetachFromControllerPendingDestroy();
		contr->Possess(mountedChar);
	}
}

void UACFRiderComponent::Internal_Ride(bool inIsRiding){
	bIsRiding = inIsRiding;
	OnRidingStateChanged.Broadcast(bIsRiding);
	if (Mount) {
		Mount->SetMounted(bIsRiding);
		if (bIsRiding) {
			Mount->SetRider(charOwner);
			Internal_AttachToMount();
		}
	}
}

void UACFRiderComponent::Internal_AttachToMount()
{
	ACharacter* mountedChar = Cast< ACharacter>(Mount->GetOwner());
	if (!mountedChar) {
		StartDismount();
		return;
	}
	charOwner->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	charOwner->AttachToComponent(mountedChar->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale,
		Mount->GetMountPoint());
	charOwner->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);

}

void UACFRiderComponent::Internal_Mount()
{
	Internal_Ride(true);

}



void UACFRiderComponent::FinishDismount(const FName& dismountPoint /*= NAME_None*/)
{
	if (charOwner && bIsRiding && Mount) {
		charOwner->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		charOwner->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		charOwner->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);

		UACFAnimationPointComponent* pointComp = Mount->GetDismountPoint(dismountPoint);
		if (pointComp) {
			charOwner->SetActorLocation(pointComp->GetComponentLocation());
			FRotator newRot(0.f, charOwner->GetActorRotation().Yaw, 0.f);
			charOwner->SetActorRotation(newRot);
		}

		ACharacter* mountChar = Mount->GetMountOwner();
		if (mountChar) {
			AController* contr = mountChar->GetController();
			if (contr && bPossessMount) {
				contr->Possess(charOwner);
				mountChar->SpawnDefaultController();
				//QUICK AND DIRTY FIX
				FRotator rot = contr->GetControlRotation();
				rot.Roll = 0.f;
				contr->SetControlRotation(rot);
			}

		}
		Internal_Ride(false);
	}
}

class ACharacter* UACFRiderComponent::GetMount() const
{
	if (Mount) {
		return Mount->GetMountOwner();
	}
	return nullptr;
}

void UACFRiderComponent::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UACFRiderComponent, bIsRiding);
	DOREPLIFETIME(UACFRiderComponent, Mount);
}