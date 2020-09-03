// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include <Engine/DataTable.h>
#include "ACFAbilityTypes.h"
#include "ACFAbilityFunctionLibrary.generated.h"


UCLASS()
class ABILITYSYSTEM_API UACFAbilityFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()	
	
public:
	
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = ACFLibrary)
	static bool GetAbilityFromDB( const FName& inName, FAbilityConfig& outAbility, const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = ACFLibrary)
	static bool GetAbilitiesFromDB( const TArray<FName>& inName, TArray<FAbilityConfig>& outAbility, const UObject* WorldContextObject);


};
