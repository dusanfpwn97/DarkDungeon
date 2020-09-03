// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ACFSavableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable)
class UACFSavableInterface : public UInterface
{
	GENERATED_BODY()

};

/**
 * 
 */
class ASCENTCOMBATFRAMEWORK_API IACFSavableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = ACF)
	void OnActorSaved();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = ACF)
	void OnActorLoaded();


};
