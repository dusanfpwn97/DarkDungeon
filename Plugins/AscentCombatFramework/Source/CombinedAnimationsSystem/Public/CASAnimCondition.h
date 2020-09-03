// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CASAnimCondition.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, abstract, EditInlineNew, HideCategories = ("DoNotShow"), CollapseCategories, AutoExpandCategories = ("CAS"))
class COMBINEDANIMATIONSSYSTEM_API UCASAnimCondition : public UObject
{
	GENERATED_BODY()

	friend class UCASAnimSlaveComponent;
public:

	bool Internal_VerifyCondition( class UCASAnimSlaveComponent* ownerComp, const FName& animTag, const ACharacter* animMaster);

protected:

	UFUNCTION(BlueprintNativeEvent, Category = CAS)
		bool VerifyCondition(const FName& animTag, const ACharacter* animMaster) ;
	virtual bool VerifyCondition_Implementation(const FName& animTag, const class ACharacter* animMaster)  { return true; }

	UFUNCTION(BlueprintPure, Category = CAS)
	class UCASAnimSlaveComponent* GetOwnerComponent() const {
		return ownerCompoment;
	}

	UPROPERTY()
	class UCASAnimSlaveComponent* ownerCompoment;

	UWorld* GetWorld() const override;
	
};

UCLASS(NotBlueprintable, BlueprintType, EditInlineNew, HideCategories = ("DoNotShow"), CollapseCategories, AutoExpandCategories = ("CAS"))
class COMBINEDANIMATIONSSYSTEM_API UCASORCondition : public UCASAnimCondition
{
	GENERATED_BODY()

protected:
	UCASORCondition() { }

	UPROPERTY(Instanced, EditDefaultsOnly, Category = "Conditions")
	TArray<UCASAnimCondition*> OrConditions;

	virtual bool VerifyCondition_Implementation(const FName& animTag, const class ACharacter* animMaster) override
	{
		for ( auto& cond : OrConditions)
		{
			if (cond->Internal_VerifyCondition(ownerCompoment, animTag, animMaster))
				return true;
		}
		return false;
	}
};

UCLASS(NotBlueprintable, BlueprintType, EditInlineNew, HideCategories = ("DoNotShow"), CollapseCategories, AutoExpandCategories = ("CAS"))
class COMBINEDANIMATIONSSYSTEM_API UCASANDCondition : public UCASAnimCondition
{
	GENERATED_BODY()

protected:
	UCASANDCondition() { }

	UPROPERTY(Instanced, EditDefaultsOnly, Category = "Conditions")
	TArray<UCASAnimCondition*> ANDConditions;

	virtual bool VerifyCondition_Implementation(const FName& animTag, const class ACharacter* animMaster)  override
	{
		for ( auto& cond : ANDConditions)
		{
			if (!cond->Internal_VerifyCondition(ownerCompoment, animTag, animMaster))
				return false;
		}
		return true;
	}
};
