// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.


#include "ACFExecutorComponent.h"
#include <GameFramework/Actor.h>
#include "Actors/ACFCharacter.h"
#include "Items/ACFWeapon.h"
#include <Animation/AnimMontage.h>
#include "Game/ACFData.h"
#include "Components/ACFActionsManagerComponent.h"
#include "CCMCameraFunctionLibrary.h"
#include "ATSBaseTargetComponent.h"
#include "Components/ACFEquipmentComponent.h"
#include "Game/ACFFunctionLibrary.h"
#include "Components/ACFActionsManagerComponent.h"
#include "CCMPlayerCameraManager.h"
#include "CCMCameraFunctionLibrary.h"
#include <GameFramework/Controller.h>
#include "Components/ACFDamageHandlerComponent.h"


// Sets default values for this component's properties
UACFExecutorComponent::UACFExecutorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UACFExecutorComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UACFExecutorComponent::OnCombinedAnimStarted(const FName& animTag)
{
	SetCharacterActionsLock(GetCharacterOwner(), true);
	SetCharacterActionsLock(GetCharacterSlave(), true);


	if (currentBestExec.CameraEvent != NAME_None) {
		ACCMPlayerCameraManager* cameraManager = UCCMCameraFunctionLibrary::GetLocalCinematicCameraManager(this);
		if (cameraManager) {
			cameraManager->TriggerCameraSequence(GetCharacterOwner(), currentBestExec.CameraEvent);
		}

	}
}

void UACFExecutorComponent::OnCombinedAnimEnded(const FName& animTag)
{
	SetCharacterActionsLock(GetCharacterOwner(), false);
	SetCharacterActionsLock(GetCharacterSlave(), false);

	if (currentBestExec.bIsFatal) {
		AACFCharacter* acfChar = Cast< AACFCharacter>(GetCharacterSlave());
		if (acfChar) {		
			acfChar->SetDeathType(EDeathType::EDestroyImmediately);
			acfChar->KillCharacter(true);
		}
	}
}

bool UACFExecutorComponent::TryExecuteCharacter( class ACharacter* target)
{
	if (!GetCharacterOwner()) {
		return false;
	}

	if (!target || target->IsPendingKill()) {
		return false;
	}

	AACFCharacter* acfCHar = Cast<AACFCharacter>(target);
	if (acfCHar && !acfCHar->IsEntityAlive()) {
		return false;
	}

	FName animTag = GetBestExecutionTagForCharacter(target);
	return TryPlayCombinedAnimation(target, animTag);
}

bool UACFExecutorComponent::TryExecuteCurrentTarget()
{
	if (!GetCharacterOwner() || !GetCharacterOwner()->GetController()) {
		return false;
	}
	
	const UATSBaseTargetComponent* targetComp = GetCharacterOwner()->GetController()->FindComponentByClass<UATSBaseTargetComponent>();
	if (targetComp) {
		ACharacter* target = Cast< ACharacter>(targetComp->GetCurrentTarget());
		if (target) {
			TryExecuteCharacter(target);
		}
	}
	return false;
}

FName UACFExecutorComponent::GetBestExecutionTagForCharacter( class ACharacter* target)
{

	if (!GetCharacterOwner() || !target) {
		return NAME_None;
	}

	ERelativeDirection relDir= GetCharacterRelativedDirection(target);
	UACFEquipmentComponent* equipComp = GetCharacterOwner()->FindComponentByClass< UACFEquipmentComponent>();

	FGameplayTag weaponTag;
	if (equipComp) {
		AACFWeapon* weap = equipComp->GetCurrentMainWeapon();
		if (weap) {
			weaponTag = weap->GetWeaponType();
		}
		else {
			weaponTag = UACFFunctionLibrary::GetWeaponTypeTagRoot();
		}
	}
	
	if (TryGetBestExecutionTag(weaponTag, relDir, currentBestExec)) {
		return currentBestExec.AnimationTag;
	}
	
	if (TryGetBestExecutionTag(weaponTag, ERelativeDirection::EAny, currentBestExec)) {
		return currentBestExec.AnimationTag;
	}

	return NAME_None;
}

bool UACFExecutorComponent::TryGetBestExecutionTag(const FGameplayTag& weaponTag, ERelativeDirection dir, FExecution& outExec) {

	if (ExecutionsByDirectionAndWeaponType.Contains(dir)) {

		FExecutions exec = ExecutionsByDirectionAndWeaponType.FindChecked(dir);
		if (exec.ExecutionsByWeaponType.Contains(weaponTag)) {

			FExecutionArray array = exec.ExecutionsByWeaponType.FindChecked(weaponTag);
			int32 randIndex = FMath::RandRange(0, array.ExecutionTag.Num() - 1);

			if (array.ExecutionTag.IsValidIndex(randIndex)) {
				outExec = array.ExecutionTag[randIndex];
				return true ;
			}
		}
	}
	return false;
}

void UACFExecutorComponent::SetCharacterActionsLock(ACharacter* target, bool lockstatus)
{
	if (target) {
		AACFCharacter* acfChar = Cast< AACFCharacter>(target);
		if (acfChar) {
			acfChar->bIsImmortal = lockstatus;
		}
		UACFActionsManagerComponent* actionComp = target->FindComponentByClass< UACFActionsManagerComponent>();
		if (actionComp) {
			if (lockstatus) {
				actionComp->LockActionsTrigger();
			}
			else {
				actionComp->UnlockActionsTrigger();
			}
			
		}
	}

}
