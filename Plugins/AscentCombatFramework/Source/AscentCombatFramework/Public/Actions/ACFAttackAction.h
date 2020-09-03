// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Actions/ACFBaseAction.h"
#include "ACFAttackAction.generated.h"

/**
 * 
 */
UCLASS()
class ASCENTCOMBATFRAMEWORK_API UACFAttackAction : public UACFBaseAction
{
	GENERATED_BODY()

public: 

	UACFAttackAction();

	UFUNCTION(BlueprintPure, Category = ACF)
	FORCEINLINE uint8 GetComboCounter() { return CurrentComboIndex; }

	UFUNCTION(BlueprintCallable, Category = ACF)
	void ResetComboCounter() {
		CurrentComboIndex = 0;
	}

protected:

	virtual void OnActionStarted_Implementation() override;

	virtual void OnActionEnded_Implementation() override;

	virtual FName GetMontageSectionName_Implementation() override;

	virtual void OnSubActionStateEntered_Implementation() override;

	virtual void OnSubActionStateExited_Implementation() override;

	virtual void OnActionTransition_Implementation(class UACFBaseAction* previousState) override;

	uint8 CurrentComboIndex = 0;

	UPROPERTY(EditDefaultsOnly, Category = ACF)
	FSnapConfiguration AttackSnapConfig;

	UPROPERTY(EditDefaultsOnly, Category = ACF)
	float RotationRateMultiplierDuringPreWinding = 1.f;

	UPROPERTY(EditDefaultsOnly, Category = ACF)
	float RotationRateMultiplierDuringSwing = 0.5f;
	
	UPROPERTY(EditDefaultsOnly, Category = ACF)
	float RotationRateMultiplierAfterWinding = 1.f;

	UPROPERTY(EditDefaultsOnly, Category = ACF)
	EDamageActivationType DamageToActivate;

	UPROPERTY(EditDefaultsOnly, Category = ACF)
	TArray<FName> TraceChannels;


private :

	float oldRotationRate;

	bool bSuccesfulCombo = false;

};
