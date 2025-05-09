// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ACFBaseCommand.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, abstract, EditInlineNew, HideCategories = ("DoNotShow"), CollapseCategories, AutoExpandCategories = ("Default"))
class ASCENTCOMBATFRAMEWORK_API UACFBaseCommand : public UObject
{
	GENERATED_BODY()

public: 

	friend class UACFCommandsManagerComponent;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = ACF)
	float EstimatedDurationWait = 1.f;

protected:


	UFUNCTION(BlueprintNativeEvent, Category = ACF)
		void ExecuteCommand(class AACFAIController* controller);
	virtual void ExecuteCommand_Implementation(class AACFAIController* controller);


	UFUNCTION(BlueprintNativeEvent, Category = ACF)
		void EndCommand(class AACFAIController* controller);
	virtual void EndCommand_Implementation(class AACFAIController* controller);




	
};



