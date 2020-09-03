// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ACFDamageType.h"
#include "ACFDamageCalculation.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, Abstract)
class ASCENTCOMBATFRAMEWORK_API UACFDamageCalculation : public UObject
{
	GENERATED_BODY()

public: 

	UFUNCTION(BlueprintNativeEvent, Category = ACF)
		void CalculateFinalDamage(const FACFDamageEvent& inDamageEvent, FACFDamageEvent& outFinalDamage);
	virtual void CalculateFinalDamage_Implementation(const FACFDamageEvent& inDamageEvent, FACFDamageEvent& outFinalDamage);

	
};
