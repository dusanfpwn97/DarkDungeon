// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Game/ACFData.h"
#include <UObject/Interface.h>
#include "ACFEntityInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UACFEntityInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ASCENTCOMBATFRAMEWORK_API IACFEntityInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = ACF)
		ETeam GetEntityCombatTeam();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = ACF)
		bool IsEntityAlive();
};
