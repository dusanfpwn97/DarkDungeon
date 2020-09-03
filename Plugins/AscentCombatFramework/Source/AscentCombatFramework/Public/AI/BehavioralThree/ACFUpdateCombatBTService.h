// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "Game/ACFData.h"
#include "ACFUpdateCombatBTService.generated.h"

/**
 * 
 */
UCLASS()
class ASCENTCOMBATFRAMEWORK_API UACFUpdateCombatBTService : public UBTService
{
	GENERATED_BODY()
	
protected:

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	void SetNewMaxComboCount();

	void UpdateCombat();

	UPROPERTY(BlueprintReadOnly, Category = ACF)
	class AACFAIController*  aiController;

	UPROPERTY(BlueprintReadOnly, Category = ACF)
		class AActor*  targetActor;

	UPROPERTY(BlueprintReadOnly, Category = ACF)
		class  AACFCharacter*  CharOwner;

	UPROPERTY(BlueprintReadOnly, Category = ACF)
		class UACFCombatBehaviourComponent* combatBehav;

	UPROPERTY(BlueprintReadOnly, Category = ACF)
	uint8 MaxComboCount;
public: 

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = ACF)
	FGameplayTag SwitchCombatTypeActionTag ;


};
