// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Game/ACFData.h"
#include "ACFActionCondition.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, abstract, EditInlineNew, HideCategories = ("DoNotShow"), CollapseCategories, AutoExpandCategories = ("ACF"))
class ASCENTCOMBATFRAMEWORK_API UACFActionCondition : public UObject
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintNativeEvent, Category = ACF)
	bool IsConditionMet(const class AACFAIController* controller);
	virtual bool IsConditionMet_Implementation(const class AACFAIController* controller) { return true; }
	
};

UCLASS(NotBlueprintable, BlueprintType, EditInlineNew, HideCategories = ("DoNotShow"), CollapseCategories, AutoExpandCategories = ("ACF"))
class ASCENTCOMBATFRAMEWORK_API UACFORActionCondition : public UACFActionCondition
{
	GENERATED_BODY()

protected:
	UACFORActionCondition() { }

	UPROPERTY(Instanced, EditDefaultsOnly, Category = "Conditions")
	TArray<UACFActionCondition*> OrConditions;

	virtual bool IsConditionMet_Implementation(const class AACFAIController* controller) override
	{
		for (auto & cond : OrConditions)
		{
			if (cond->IsConditionMet(controller))
				return true;
		}
		return false;
	}
};

UCLASS(NotBlueprintable, BlueprintType, EditInlineNew, HideCategories = ("DoNotShow"), CollapseCategories, AutoExpandCategories = ("ACF"))
class ASCENTCOMBATFRAMEWORK_API UACFANDActionCondition : public UACFActionCondition
{
	GENERATED_BODY()

public:
	UACFANDActionCondition() { }

	UPROPERTY(Instanced, EditDefaultsOnly, Category = "Conditions")
	TArray<UACFActionCondition*> AndConditions;

	virtual bool IsConditionMet_Implementation(const class AACFAIController* controller) override
	{
		for (auto & cond : AndConditions)
		{
			if (!cond->IsConditionMet(controller))
				return false;
		}
		return true;
	}
};

UCLASS(NotBlueprintable, BlueprintType, EditInlineNew, HideCategories = ("DoNotShow"), CollapseCategories, AutoExpandCategories = ("ACF"))
class ASCENTCOMBATFRAMEWORK_API UACFDistanceActionCondition : public UACFActionCondition
{
	GENERATED_BODY()

public:
	UACFDistanceActionCondition() { }

	UPROPERTY(EditDefaultsOnly, Category = "Conditions")
	EConditionType ConditionType;

	UPROPERTY(EditDefaultsOnly, Category = "Conditions")
	float Distance;

	UPROPERTY(EditDefaultsOnly, Category = "Conditions")
	float NearlyEqualAcceptance = 25.f;

	virtual bool IsConditionMet_Implementation(const class AACFAIController* controller) override;
};

UCLASS(NotBlueprintable, BlueprintType, EditInlineNew, HideCategories = ("DoNotShow"), CollapseCategories, AutoExpandCategories = ("Default"))
class ASCENTCOMBATFRAMEWORK_API UACFStatisticActionCondition : public UACFActionCondition
{
	GENERATED_BODY()

public:
	UACFStatisticActionCondition() { }

	UPROPERTY(EditDefaultsOnly, Category = "Conditions")
	EConditionType ConditionType;

	UPROPERTY(EditDefaultsOnly, Category = "Conditions")
	FGameplayTag StatisticTag;

	UPROPERTY(EditDefaultsOnly, Category = "Conditions")
	float StatisticValue;

	UPROPERTY(EditDefaultsOnly, Category = "Conditions")
	float NearlyEqualAcceptance = 5.f;

	virtual bool IsConditionMet_Implementation(const class AACFAIController* controller) override;
};

