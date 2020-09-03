// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include <GameplayTagContainer.h>
#include "ARSStatisticsData.h"
#include "ARSDeveloperSettings.generated.h"

/**
 * 
 */
UCLASS(config = Plugins, defaultconfig, meta = (DisplayName = "Advanced RPG"))
class ADVANCEDRPGSYSTEM_API UARSDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:

	/*Define with Curves how your Attributes generates your Parameters and your Statistics */
	UPROPERTY(EditAnywhere, config, Category = ARS)	
	TMap<FGameplayTag, FGenerationRule> SecondaryAttGenerationRules;

	/*Define here the tag Root of your Attributes*/
	UPROPERTY(EditAnywhere, config, Category = ARS)
	FGameplayTag AttributesRoot;

	/*Define here the tag Root of your Parameters*/
	UPROPERTY(EditAnywhere, config, Category = ARS)
	FGameplayTag ParametersRoot;

	/*Define here the tag Root of your Statistics*/
	UPROPERTY(EditAnywhere, config, Category = ARS)
	FGameplayTag StatisticsRoot;
	
	/*Max Level for all your character*/
	UPROPERTY(EditAnywhere, config, Category = ARS)
	int32 MaxLevel = 100;
	
};
