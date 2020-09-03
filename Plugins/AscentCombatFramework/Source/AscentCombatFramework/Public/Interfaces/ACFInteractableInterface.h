// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ACFInteractableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable)
class UACFInteractableInterface : public UInterface
{
	GENERATED_BODY()

};

/**
 * 
 */
class ASCENTCOMBATFRAMEWORK_API IACFInteractableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = ACF)
	void OnInteractedByPawn(class APawn* Pawn);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = ACF)
	void OnInteractableRegisteredByPawn(class APawn* Pawn);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = ACF)
	void OnInteractableUnregisteredByPawn(class APawn* Pawn);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = ACF)
	FText GetInteractableName();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = ACF)
	bool CanBeInteracted(class APawn* Pawn);

};
