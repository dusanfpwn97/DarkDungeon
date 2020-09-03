// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CASAnimCondition.h"
#include <GameplayTagContainer.h>
#include "ACFExecutionCondition.generated.h"

/**
 * 
 */
UCLASS()
class EXECUTIONSSYSTEM_API UACFExecutionCondition : public UCASAnimCondition
{
	GENERATED_BODY()

protected: 

	virtual bool VerifyCondition_Implementation(const FName& animTag, const class ACharacter* animMaster) override;

	/*If this attacker parameter is above owner health, the execution can be triggered*/
	UPROPERTY(EditDefaultsOnly, Category = ACF)
	FGameplayTag ExecutorParameterToCheck;

	/*Multiplier for the Parameter, useful if y*/
	UPROPERTY(EditDefaultsOnly, Category = ACF)
	float ParameterScalarMultiplier = 1.f;

	/*Chances that the execution will be triggered*/
	UPROPERTY(EditDefaultsOnly, Category = ACF)
	float ExecutionChance = 70.f;
	
};
