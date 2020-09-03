// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include <GameplayTagContainer.h>
#include "ACFGameInstance.generated.h"


/**
 * 
 */


UCLASS()
class ASCENTCOMBATFRAMEWORK_API UACFGameInstance : public UGameInstance
{
	GENERATED_BODY()


public:

	UACFGameInstance();

	virtual void Init() override;


protected: 

	UPROPERTY(BlueprintReadWrite, Savegame, Category = "ACF")
	TArray<FName> LoadedLevels;
	UPROPERTY(BlueprintReadWrite, Savegame, Category = "ACF")
	TArray<FName> UnloadedLevels;



private: 



};
