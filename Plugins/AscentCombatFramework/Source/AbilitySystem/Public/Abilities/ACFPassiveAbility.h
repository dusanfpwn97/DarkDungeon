// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/ACFAbility.h"
#include "ARSStatisticsData.h"
#include "Game/ACFData.h"
#include "ACFPassiveAbility.generated.h"

/**
 * 
 */
UCLASS()
class ABILITYSYSTEM_API UACFPassiveAbility : public UACFAbility
{
	GENERATED_BODY()

public: 

	UACFPassiveAbility() {
		AbilityType = EAbilityType::EPassive;
	};

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ACF)
	FAttributesSetModifier StatisticModifer;

	virtual void OnAbilityActivated_Implementation() override;

	virtual void OnAbilityDeactivated_Implementation() override;
	
};
