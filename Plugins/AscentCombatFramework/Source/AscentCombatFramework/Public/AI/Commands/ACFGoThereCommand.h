// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AI/Commands/ACFBaseCommand.h"
#include "ACFGoThereCommand.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class ASCENTCOMBATFRAMEWORK_API UACFGoThereCommand : public UACFBaseCommand
{
	GENERATED_BODY()
protected: 

	UPROPERTY(EditDefaultsOnly, Category = ACF)
		bool bDrawDebug ;
	
public: 

	virtual void ExecuteCommand_Implementation(class AACFAIController* controller) override;

	virtual void EndCommand_Implementation(class AACFAIController* controller) override;
};
