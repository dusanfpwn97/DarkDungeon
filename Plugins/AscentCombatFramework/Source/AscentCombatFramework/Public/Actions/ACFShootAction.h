// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Actions/ACFBaseAction.h"
#include "ACFShootAction.generated.h"

/**
 * 
 */
UCLASS()
class ASCENTCOMBATFRAMEWORK_API UACFShootAction : public UACFBaseAction
{
	GENERATED_BODY()

	UACFShootAction();

protected:

	virtual void OnActionStarted_Implementation() override;
	
};
