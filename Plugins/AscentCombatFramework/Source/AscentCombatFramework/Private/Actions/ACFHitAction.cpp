// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#include "Actions/ACFHitAction.h"
#include "Actions/ACFBaseAction.h"
#include "Actors/ACFCharacter.h"
#include "Animation/ACFAnimInstance.h"
#include "Game/ACFFunctionLibrary.h"
#include "Components/ACFLocomotionComponent.h"

UACFHitAction::UACFHitAction()
{
	HitDirectionToMontageSectionMap.Add(EDirection::Front, FName("Front"));
	HitDirectionToMontageSectionMap.Add(EDirection::Back, FName("Back"));
	HitDirectionToMontageSectionMap.Add(EDirection::Right, FName("Right"));
	HitDirectionToMontageSectionMap.Add(EDirection::Left, FName("Left"));
	ActionConfig.MontageReproductionType = EMontageReproductionType::ECurveOverrideSpeedAndDirection;
	ActionConfig.bStopBehavioralThree = true;
}

void UACFHitAction::OnActionStarted_Implementation()
{
	Super::OnActionStarted_Implementation();

	if (CharacterOwner)
	{				
		damageReceived = CharacterOwner->GetLastDamageInfo();
		UACFActionsManagerComponent* actionsMan = CharacterOwner->GetActionsComponent();
		if (actionsMan)
		{
			actionsMan->StoreAction(UACFFunctionLibrary::GetDefaultActionsState());
		}
	}
	if (ActionConfig.MontageReproductionType == EMontageReproductionType::ECurveOverrideSpeedAndDirection)
	{
		FVector damageMomentum = UACFFunctionLibrary::GetActorsRelativeDirectionVector(damageReceived);

		if (CharacterOwner)
		{
			UACFLocomotionComponent* locComp = CharacterOwner->GetLocomotionComponent();
			locComp->StartOverrideSpeedAndDirection(damageMomentum);
		}
	}
	

}

void UACFHitAction::OnActionEnded_Implementation()
{
	Super::OnActionEnded_Implementation();
	if (ActionConfig.MontageReproductionType == EMontageReproductionType::ECurveOverrideSpeedAndDirection)
	{
		if (CharacterOwner)
		{
			UACFLocomotionComponent* locComp = CharacterOwner->GetLocomotionComponent();
			locComp->StopOverrideSpeedAndDirection();
		}
	}
}

FName UACFHitAction::GetMontageSectionName_Implementation()
{

	EDirection dir = damageReceived.DamageDirection;

		FName *section = HitDirectionToMontageSectionMap.Find(dir);

		if (section)
		{
			return *section;
		}
		 
	
	return Super::GetMontageSectionName_Implementation();
}
