// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include <GameplayTagContainer.h>
#include <Curves/CurveFloat.h>
#include "Game/ACFData.h"
#include "ACFDeveloperSettings.generated.h"

enum class EDamageZone : uint8;

UCLASS(config = Plugins, Defaultconfig, meta = (DisplayName = "AscentCombatFramework"))
class ASCENTCOMBATFRAMEWORK_API UACFDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:


	UPROPERTY(EditAnywhere, config, Category = "ACF | Root Tags")
	FGameplayTag DefaultActionsState;

	UPROPERTY(EditAnywhere, config, Category = "ACF | Root Tags")
	FGameplayTag DefaultHitState;

	UPROPERTY(EditAnywhere, config, Category = "ACF | Root Tags")
	FGameplayTag DefaultDeathState;

	UPROPERTY(EditAnywhere, config, Category = "ACF | Root Tags")
	FGameplayTag HealthTag;

	UPROPERTY(EditAnywhere, config, Category = "ACF | Root Tags")
	FGameplayTag BaseMovementTypeTag;

	UPROPERTY(EditAnywhere, config, Category = "ACF | Root Tags")
	FGameplayTag WeaponTypeTag;

	UPROPERTY(EditAnywhere, config, Category = "ACF | Root Tags")
	FGameplayTag WeaponSlotsTag;

	UPROPERTY(EditAnywhere, config, Category = "ACF | Root Tags")
	FGameplayTag MovesetTypeTag;

	UPROPERTY(EditAnywhere, config, Category = "ACF | Root Tags")
	FGameplayTag AnimationOverlayTag;

	UPROPERTY(EditAnywhere, config, Category = "ACF | Root Tags")
	FGameplayTag EnchantmentsTag;

// 	UPROPERTY(EditAnywhere, config, Category = "ACF | Root Tags")     
// 	FGameplayTag ArmorSlotsTag;

	UPROPERTY(EditAnywhere, config, Category = "ACF | Default Values")
	float DefaultRandomDamageDeviationPercentage = 5.0f;
	
	UPROPERTY(EditAnywhere, config, Category = "ACF | Default Values")
	TMap<EDamageZone, float> DamageZoneToDamageMultiplier;

	UPROPERTY(EditAnywhere, config, Category = "ACF | Default Classes")
	TSubclassOf<class AACFWorldItem> WorldItemClass;

	UPROPERTY(EditAnywhere, config, Category = "ACF | Default Classes")
	TSubclassOf<class UACFDamageCalculation> DamageCalculatorClass;
// 
// 	UPROPERTY(EditAnywhere, config, Category = "ACF | Socket Names")
// 	TMap<FGameplayTag, FName> OnBodySocketsByWeaponType;
// 
// 	UPROPERTY(EditAnywhere, config, Category = "ACF | Socket Names")
// 	TMap<FGameplayTag, FName> EquippedSocketsByWeaponType;
	
};
   