// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Actors/ACFCharacter.h"
#include "Components/ACFLocomotionComponent.h"
#include "Game/ACFDamageType.h"
#include "Game/ACFData.h"
#include <Components/ActorComponent.h>
#include "ACFCombatBehaviourComponent.generated.h"

struct FACFDamageEvent;

/**
 * 
 */

UCLASS(ClassGroup = (ACF), Blueprintable, meta = (BlueprintSpawnableComponent))
class ASCENTCOMBATFRAMEWORK_API UACFCombatBehaviourComponent : public UActorComponent
{
	GENERATED_BODY()

	UACFCombatBehaviourComponent();
public: 

	friend class AACFAIController;

	/*The default combat behavior (melee/ranged) for this AI. Could change during combat if multiple 
	behaviors have been defined in Allowed Behaviors*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CombatConfig")
	ECombatBehaviorType DefaultCombatBehaviorType;

	/*The default combat state  for this AI, triggered once no other states are available*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CombatConfig")
	EAICombatState DefaultCombatState = EAICombatState::EMeleeCombat;

	/*The minimum amount of Actions that should be done in MeleeAttacks state before going in
	Post Attack*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CombatConfig")
	uint8 MinMeleeComboAttacks = 1;

	/*The maximum amount of Actions that should be done in MeleeAttacks state before going in
	Post Attack*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CombatConfig")
	uint8 MaxMeleeComboAttacks = 2;

	/* If this ai needs an equipped weapon to start fighting*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CombatConfig")
	bool bNeedsWeapon = false;

	/* Action to be triggered by this ai to equip a Melee weapon*/
	UPROPERTY(EditAnywhere, meta = (EditCondition = bNeedsWeapon), BlueprintReadWrite, Category = "CombatConfig")
	FGameplayTag EquipMeleeAction;

	/* Action to be triggered by this ai to equip a Ranged weapon*/
	UPROPERTY(EditAnywhere, meta = (EditCondition = bNeedsWeapon), BlueprintReadWrite, Category = "CombatConfig")
	FGameplayTag EquipRangedAction;

	/* Action to be triggered when combat starts*/
	UPROPERTY(EditAnywhere, meta = (EditCondition = bNeedsWeapon), BlueprintReadWrite, Category = "CombatConfig")
	FGameplayTag EngagingAction;

	/* The allowed combat behaviors (melee / ranged) of this AI*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CombatConfig")
	TArray<ECombatBehaviorType> AllowedBehaviors;

	/*Configuration of each Combat State*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CombatConfig")
	TMap<EAICombatState, FAICombatStateConfig> CombatStatesConfig;

	/*The actions that should be performed by the AI for every combat state */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CombatConfig | Actions")
	TMap<EAICombatState, FActionsChances> ActionByCombatState;

	/*The actions that should be triggered when this ai got hit and the conditional triggers.
	Used to define automatic actions like Dodging/parrying/counterattacking or just playing hit animations*/
 	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CombatConfig | Actions")
 	TArray<FOnHitActionChances> HitResponseActions;

	/*Generic conditionals action you can define by creating your own ActionCondition class*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CombatConfig | Actions")
	TArray<FConditions> ActionByCondition;

	UFUNCTION(BlueprintCallable, Category = ACF)
	bool TryExecuteActionByCombatState(EAICombatState combatState);

	UFUNCTION(BlueprintCallable, Category = ACF)
	bool TryExecuteConditionAction();

	UFUNCTION(BlueprintCallable, Category = ACF)
	FGameplayTag EvaluateHitResponse(const FACFDamageEvent& damageEvent);

	UFUNCTION(BlueprintPure, Category = ACF)
	bool IsTargetInMeleeRange(AActor* target);

	UFUNCTION(BlueprintPure, Category = ACF)
	EAICombatState GetBestCombatStateByTargetDistance(float targetDistance);

	UFUNCTION(BlueprintCallable, Category = ACF)
	float GetIdealDistanceByCombatState(EAICombatState combatState) const;

	bool EvaluateCombatState(EAICombatState combatState);
	
	bool ShouldExecuteAction(FActionChances action);

private: 

	bool VerifyCondition(FConditions condition);

	void InitBehavior(class AACFAIController* _controller);

	void TryEquipWeapon();

	void UninitBehavior();

	bool CheckEquipment();

	bool EvaluetHitResponseAction(const FOnHitActionChances& action, const FACFDamageEvent& damageEvent);

	UPROPERTY()
	class AACFCharacter* characterOwner;

	UPROPERTY()
	class AACFAIController* aiController;
	 
/*	void UpdateBehaviorType();*/
};
