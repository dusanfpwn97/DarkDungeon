// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#include "AI/Components/ACFCombatBehaviourComponent.h"
#include "Actors/ACFCharacter.h"
#include "AI/ACFAIController.h"
#include "Components/ACFEquipmentComponent.h"
#include "Game/ACFData.h"
#include "AI/ACFActionCondition.h"
#include "Game/ACFFunctionLibrary.h"

UACFCombatBehaviourComponent::UACFCombatBehaviourComponent()
{

	CombatStatesConfig.Add(EAICombatState::EMeleeCombat, FAICombatStateConfig(120.f, 100.f,ELocomotionState::EWalk));
	CombatStatesConfig.Add(EAICombatState::EMeleePostAttack, FAICombatStateConfig(120.f, 90.f, ELocomotionState::EWalk));
	CombatStatesConfig.Add(EAICombatState::EStudyTarget, FAICombatStateConfig(500.f, 75.f, ELocomotionState::EWalk));
	CombatStatesConfig.Add(EAICombatState::ERangedCombat, FAICombatStateConfig(700.f, 100.f, ELocomotionState::EWalk));
	AllowedBehaviors.Add(ECombatBehaviorType::EMelee);
}



bool UACFCombatBehaviourComponent::TryExecuteActionByCombatState(EAICombatState combatState)
{
	if (CheckEquipment())
	{
		TryEquipWeapon();
		return false;
	}

	FActionsChances* actions = ActionByCombatState.Find(combatState);
	if (actions)
	{
		for (auto& elem : actions->PossibleActions)
		{
			if (ShouldExecuteAction(elem))
			{
				aiController->SetWaitDurationTimeBK(elem.BTWaitTime);
				characterOwner->TriggerAction(elem.ActionTag, elem.Priority);
				return true;
			}
		}
	}
	return false;
}

bool UACFCombatBehaviourComponent::TryExecuteConditionAction()
{
	if (CheckEquipment())
	{
		TryEquipWeapon();
		return false;
	}

	for (auto actionCond : ActionByCondition)
	{
		FActionChances * action = &actionCond;
		if (VerifyCondition(actionCond) && ShouldExecuteAction(*action))
		{
			aiController->SetWaitDurationTimeBK(actionCond.BTWaitTime);
			characterOwner->TriggerAction(actionCond.ActionTag, actionCond.Priority);
			return true;
		}
	}
	return false;
}

// bool UACFCombatBehaviourComponent::TryExecuteConditionCommand()
// {
// 	return false;
// }

bool UACFCombatBehaviourComponent::VerifyCondition(FConditions condition)
{
	return condition.Condition && condition.Condition->IsConditionMet(aiController);
}

FGameplayTag UACFCombatBehaviourComponent::EvaluateHitResponse(const FACFDamageEvent& damageEvent)
{
	if ( characterOwner)
	{
		for (auto& elem : HitResponseActions)
		{
			if (ShouldExecuteAction(elem) && EvaluetHitResponseAction(elem, damageEvent))
			{
				return elem.ActionTag;
			}
		}
	}
 	return FGameplayTag();
}



bool UACFCombatBehaviourComponent::IsTargetInMeleeRange( AActor* target )
{
	const FAICombatStateConfig *meleeDist = CombatStatesConfig.Find(EAICombatState::EMeleeCombat);

	const ACharacter* targetChar = Cast<ACharacter>(target);
	if (meleeDist) {
		if (targetChar) {
			float dist = UACFFunctionLibrary::CalculateDistanceBetweenCharactersExtents(characterOwner, targetChar);
			return meleeDist->IdealDistance >= dist;
		}
		else if(target) {
			return characterOwner->GetDistanceTo(target) <= meleeDist->IdealDistance;
		}
	}		
	return false;
}



EAICombatState UACFCombatBehaviourComponent::GetBestCombatStateByTargetDistance(float targetDistance)
{
	if (targetDistance == 0) {
		characterOwner->TriggerAction(EngagingAction, EActionPriority::EMedium);
		return EAICombatState::EFlee;

	}

	const bool bInMeleeRange = IsTargetInMeleeRange(aiController->GetTargetActorBK());
	if (bInMeleeRange && EvaluateCombatState(EAICombatState::EMeleeCombat) && AllowedBehaviors.Contains(ECombatBehaviorType::EMelee))
	{
		DefaultCombatBehaviorType = ECombatBehaviorType::EMelee;
		return EAICombatState::EMeleeCombat;
	}
	if (aiController->GetCombatStateBK() == EAICombatState::EMeleePostAttack)
	{
		return EAICombatState::EMeleePostAttack;
	}
		
	const FAICombatStateConfig* strafeDist = CombatStatesConfig.Find(EAICombatState::EStudyTarget);
	if (strafeDist && EvaluateCombatState(EAICombatState::EStudyTarget) && targetDistance < strafeDist->IdealDistance && !bInMeleeRange )
	{
		return EAICombatState::EStudyTarget;
	}
	
	const FAICombatStateConfig* rangedDist = CombatStatesConfig.Find(EAICombatState::ERangedCombat);
	if (rangedDist && targetDistance > rangedDist->IdealDistance && EvaluateCombatState(EAICombatState::ERangedCombat) && AllowedBehaviors.Contains(ECombatBehaviorType::ERanged))
	{
		DefaultCombatBehaviorType = ECombatBehaviorType::ERanged;
		return EAICombatState::ERangedCombat;
	}

	const FAICombatStateConfig* fleeDist = CombatStatesConfig.Find(EAICombatState::EFlee);
	if (fleeDist && targetDistance < fleeDist->IdealDistance  && EvaluateCombatState(EAICombatState::EFlee) )
	{
		return EAICombatState::EFlee;
	}

	return DefaultCombatState;
}

float UACFCombatBehaviourComponent::GetIdealDistanceByCombatState(EAICombatState combatState) const
{
	const FAICombatStateConfig* aiState = CombatStatesConfig.Find(combatState);
	if (aiState) {
		return aiState->IdealDistance;
	}

	UE_LOG(LogTemp, Warning, TEXT("Unallowed Combat State! - UACFCombatBehaviourComponent::GetIdealDistanceByCombatState"));
	return -1.f;
}

bool UACFCombatBehaviourComponent::ShouldExecuteAction(FActionChances action)
{
	return characterOwner && characterOwner->GetActionsComponent() && 
		characterOwner->GetActionsComponent()->CanExecuteAction(action.ActionTag) && 
		FMath::RandRange(0.f, 100.f) < action.ChancePercentage &&	(
		(uint8)characterOwner->GetRelativeTargetDirection( characterOwner->GetTarget()) == (uint8)action.AllowedFromDirection || 
		action.AllowedFromDirection == EActionDirection::EveryDirection
			);
}

void UACFCombatBehaviourComponent::InitBehavior(class AACFAIController* _controller)
{
	if (_controller)
	{
		aiController = _controller;

		characterOwner = Cast<AACFCharacter>(_controller->GetPawn());

		if (characterOwner && characterOwner->GetLocomotionComponent())
		{
			characterOwner->SetStrafeMovement(characterOwner->GetLocomotionComponent()->IsCharacterStrafing());
		}	

		if (CheckEquipment())
		{
			TryEquipWeapon();
		}
	}
}

void UACFCombatBehaviourComponent::TryEquipWeapon()
{
	UACFEquipmentComponent* equipComp = characterOwner->GetEquipmentComponent();

	ensure(equipComp);

	if (DefaultCombatBehaviorType == ECombatBehaviorType::EMelee)
	{
		characterOwner->TriggerAction(EquipMeleeAction, EActionPriority::EHigh);
		aiController->SetCombatStateBK(EAICombatState::EMeleeCombat);
	}
	else if (DefaultCombatBehaviorType == ECombatBehaviorType::ERanged)
	{
		characterOwner->TriggerAction(EquipRangedAction, EActionPriority::EHigh);
		aiController->SetCombatStateBK(EAICombatState::ERangedCombat);
	}

}

void UACFCombatBehaviourComponent::UninitBehavior()
{

	if (bNeedsWeapon && characterOwner && characterOwner->GetCombatType() != ECombatType::EUnarmed)
	{
		UACFEquipmentComponent* equipComp = characterOwner->GetEquipmentComponent();

		ensure(equipComp);
		FGameplayTag unequipAction = DefaultCombatBehaviorType == ECombatBehaviorType::EMelee ? EquipMeleeAction : EquipRangedAction;
		characterOwner->TriggerAction(unequipAction, EActionPriority::EHighest);
		characterOwner->SetStrafeMovement(false);
	}

}

bool UACFCombatBehaviourComponent::CheckEquipment()
{	
	return (characterOwner && characterOwner->GetCombatType() != ECombatType::EMelee && bNeedsWeapon && DefaultCombatBehaviorType == ECombatBehaviorType::EMelee) ||
		(characterOwner && characterOwner->GetCombatType() != ECombatType::ERanged && bNeedsWeapon && DefaultCombatBehaviorType == ECombatBehaviorType::ERanged) ;	   
}

bool UACFCombatBehaviourComponent::EvaluetHitResponseAction(const FOnHitActionChances& action, const FACFDamageEvent& damageEvent)
{
	if ((uint8)damageEvent.DamageDirection != (uint8)action.AllowedFromDirection &&
		action.AllowedFromDirection != EActionDirection::EveryDirection)
		return false;

	for (TSubclassOf<UDamageType> damageType : action.AllowedDamageTypes)
	{
		if (damageEvent.DamageClass->IsChildOf(damageType))
			return true;
	}
	return false;
}

bool UACFCombatBehaviourComponent::EvaluateCombatState(EAICombatState combatState)
{
	if (!CombatStatesConfig.Contains(combatState)) {
		return false;
	}
	FAICombatStateConfig* chance = CombatStatesConfig.Find(combatState);

	if (chance) {
		return FMath::RandRange(0.f, 100.f) <= chance->TriggerChancePercentage;
	}
	return false;
}



// void UACFCombatBehaviourComponent::UpdateBehaviorType()
// {
// 	if (IdealDistanceByCombatState.Contains(ECombatBehaviorType::ERanged))
// 	{	
// 		float* randegdist = IdealDistanceByCombatState.Find(ECombatBehaviorType::ERanged);
// 		if (randegdist &&  aiController->GetTargetActorDistanceBK() > *randegdist)
// 		{
// 			CurrentCombatBehaviorType = ECombatBehaviorType::ERanged;
// 			return;
// 		}			
// 	}
// 	CurrentCombatBehaviorType = ECombatBehaviorType::EMelee;
// }
