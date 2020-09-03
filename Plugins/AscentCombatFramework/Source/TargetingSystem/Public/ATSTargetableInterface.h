// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ATSTargetableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable)
class UATSTargetableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TARGETINGSYSTEM_API IATSTargetableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	IATSTargetableInterface();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = ATS)
	void OnTargetAcquired(class UATSTargetPointComponent* point);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = ATS)
	void OnTargetLosed();
};
