// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/ACFAbility.h"
#include "Game/ACFData.h"
#include <GameplayTagContainer.h>
#include "ACFActionAbility.generated.h"

/**
 * 
 */
UCLASS()
class ABILITYSYSTEM_API UACFActionAbility : public UACFAbility
{
	GENERATED_BODY()
	
	UACFActionAbility() {
		AbilityType = EAbilityType::EActive;
	};

protected:

	UPROPERTY(EditDefaultsOnly, Category = ACF)
	FGameplayTag ActionsToTrigger;

	UPROPERTY(EditDefaultsOnly, Category = ACF)
	EActionPriority AbilityPriority;

	void OnAbilityActivated_Implementation() override;
	
};
