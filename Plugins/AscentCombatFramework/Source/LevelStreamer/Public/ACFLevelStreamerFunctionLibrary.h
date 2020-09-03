// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ACFLevelStreamerFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class LEVELSTREAMER_API UACFLevelStreamerFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public: 


	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = ACFStreamerLibrary)
	static TArray<FName> GetAllActiveLevels(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = ACFStreamerLibrary)
	static TArray<FName> GetAllLevelsInPersistent(const UObject* WorldContextObject);
	
};
