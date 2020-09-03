// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#include "Actions/ACFAttackAction.h"
#include "Actions/ACFBaseAction.h"
#include "Components/ACFActionsManagerComponent.h"
#include "Actors/ACFCharacter.h"
#include "Animation/ACFAnimInstance.h"
#include <GameFramework/CharacterMovementComponent.h>
#include "Components/ACFLocomotionComponent.h"





UACFAttackAction::UACFAttackAction()
{
	AttackSnapConfig.maxSnapMultiplier = 2.5f;
	AttackSnapConfig.preferredDistance = 100.f;
}

void UACFAttackAction::OnActionStarted_Implementation()
{
	Super::OnActionStarted_Implementation();
	if (CharacterOwner && ActionConfig.MontageReproductionType == EMontageReproductionType::ECurveSnapsOnTarget)
	{
		UACFLocomotionComponent* locComp = CharacterOwner->GetLocomotionComponent();
		if (locComp && CharacterOwner->GetTarget())
		{
			FSnapConfiguration SnapConfig;
			SnapConfig.maxSnapMultiplier = AttackSnapConfig.maxSnapMultiplier;
			SnapConfig.preferredDistance = AttackSnapConfig.preferredDistance;
			SnapConfig.target = CharacterOwner->GetTarget();
			locComp->StartSnapping(SnapConfig);
		}

		UCharacterMovementComponent* moveComp = CharacterOwner->GetCharacterMovement();

		if (moveComp)
		{
			oldRotationRate = moveComp->RotationRate.Yaw;
			moveComp->RotationRate.Yaw = oldRotationRate * RotationRateMultiplierDuringPreWinding;
		}
		
	}
	bSuccesfulCombo = false;
}

void UACFAttackAction::OnActionEnded_Implementation()
{
	Super::OnActionEnded_Implementation();
	if (CharacterOwner && ActionsManager)
	{
		CharacterOwner->DeactivateDamage(DamageToActivate, TraceChannels);
	}

	if (CharacterOwner && ActionConfig.MontageReproductionType == EMontageReproductionType::ECurveSnapsOnTarget)
	{
		UACFLocomotionComponent* locComp = CharacterOwner->GetLocomotionComponent();
		if (locComp)
		{
			locComp->StopSnapping();
		}
		UCharacterMovementComponent* moveComp = CharacterOwner->GetCharacterMovement();
		if (moveComp)
		{
			moveComp->RotationRate.Yaw = oldRotationRate;
		}
	}
	if (!bSuccesfulCombo)
	{
		CurrentComboIndex = 0;
	}
	
		
}


FName UACFAttackAction::GetMontageSectionName_Implementation()
{

	if (animMontage)
	{
		 FName SectionName = animMontage->GetSectionName(CurrentComboIndex);

		 if (SectionName != NAME_None)
		 {
			 return SectionName;
		 }
		 else    
		 {
			 CurrentComboIndex = 0; 
			 return animMontage->GetSectionName(CurrentComboIndex);
		 }

	}
	return NAME_None;
}

void UACFAttackAction::OnSubActionStateEntered_Implementation()
{
	Super::OnSubActionStateEntered_Implementation();

	if (CharacterOwner && ActionsManager)
	{
		CharacterOwner->ActivateDamage(DamageToActivate, TraceChannels);
		
		UCharacterMovementComponent* moveComp = CharacterOwner->GetCharacterMovement();

		if (moveComp)
		{
			moveComp->RotationRate.Yaw = oldRotationRate * RotationRateMultiplierDuringSwing;
		}	
	
	}
}

void UACFAttackAction::OnSubActionStateExited_Implementation()
{
	Super::OnSubActionStateExited_Implementation();

	if (CharacterOwner && ActionsManager)
	{
		CharacterOwner->DeactivateDamage(DamageToActivate, TraceChannels);
	}

	UCharacterMovementComponent* moveComp = CharacterOwner->GetCharacterMovement();

	if (moveComp)
	{
		moveComp->RotationRate.Yaw = oldRotationRate * RotationRateMultiplierAfterWinding;
	}
}


void UACFAttackAction::OnActionTransition_Implementation(class UACFBaseAction* previousState)
{
	if (previousState && previousState->IsA(UACFAttackAction::StaticClass()))
	{
		CurrentComboIndex++;
		bSuccesfulCombo = true;
	}
	else
	{
		CurrentComboIndex = 0;
		bSuccesfulCombo = false;
	}
}
