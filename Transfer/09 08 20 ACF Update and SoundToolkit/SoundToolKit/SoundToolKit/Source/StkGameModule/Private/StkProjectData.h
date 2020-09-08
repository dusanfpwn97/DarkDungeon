//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#pragma once

#include "Engine/DataAsset.h"

#include "StkProjectData.generated.h"

UCLASS()
class STKGAMEMODULE_API UStkProjectData : public UDataAsset
{
	GENERATED_BODY()

public:
	static void Init();
	static void Create();
	static UStkProjectData* Get();

public:
	UPROPERTY()
	TMap<UObject*, class UStkAcousticData*> StkArchetypesAcousticData;

private:
	static UStkProjectData* StkProjectData;
};
