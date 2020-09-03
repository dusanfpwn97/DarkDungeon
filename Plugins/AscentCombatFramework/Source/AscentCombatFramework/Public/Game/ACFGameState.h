// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "ACFData.h"
#include "ACFGameState.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBattleStateChanged, const EBattleState&, battleState);

UCLASS()
class ASCENTCOMBATFRAMEWORK_API AACFGameState : public AGameState
{
	GENERATED_BODY()
private:

	void UpdateBattleState();

protected: 

	UPROPERTY(EditDefaultsOnly, Category = ACF)
	EBattleType BattleType = EBattleType::ETeamBased;

	EBattleState gameState = EBattleState::EExploration;

	UPROPERTY()
	TArray<class AACFAIController*> InBattleAIs;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ACF)
	class UACFEffectsDispatcherComponent* EffectsComp;

public:

	AACFGameState();

	UFUNCTION(BlueprintPure, Category = ACF)
	FORCEINLINE EBattleType GetBattleType() const { return BattleType; }

	UFUNCTION(BlueprintPure, Category = ACF)
	FORCEINLINE EBattleState GetBattleState() const { return gameState; }

	UFUNCTION(BlueprintPure, Category = ACF)
	FORCEINLINE class UACFEffectsDispatcherComponent* GetEffectsComponent() const { return EffectsComp; }

	void AddAIToBattle(class AACFAIController* contr);
	void RemoveAIFromBattle(class AACFAIController* contr);

	UPROPERTY(BlueprintAssignable, Category = ACF)
	FOnBattleStateChanged OnBattleStateChanged;
	
};
