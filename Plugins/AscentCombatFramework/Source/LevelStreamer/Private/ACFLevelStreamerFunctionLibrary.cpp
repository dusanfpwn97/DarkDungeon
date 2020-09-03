// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.


#include "ACFLevelStreamerFunctionLibrary.h"
#include <Kismet/GameplayStatics.h>
#include <GameFramework/PlayerController.h>
#include <Engine/LevelStreaming.h>
#include <Engine/World.h>


TArray<FName> UACFLevelStreamerFunctionLibrary::GetAllActiveLevels(const UObject* WorldContextObject)
{
	TArray<FName> names;

	APlayerController* playerController = UGameplayStatics::GetPlayerController(WorldContextObject, 0);

	if (!playerController)
		return names;

	UWorld* world = playerController->GetWorld();

	if (!world)
		return names;

	const TArray<ULevelStreaming*>& levels = world->GetStreamingLevels();

	for (ULevelStreaming* level : levels)
	{
		if (level->GetCurrentState() == ULevelStreaming::ECurrentState::LoadedVisible)
			names.Add(level->PackageNameToLoad);
	}
	return names;
}

TArray<FName> UACFLevelStreamerFunctionLibrary::GetAllLevelsInPersistent(const UObject* WorldContextObject)
{
	TArray<FName> names;

	APlayerController* playerController = UGameplayStatics::GetPlayerController(WorldContextObject, 0);

	if (!playerController)
		return names;

	UWorld* world = playerController->GetWorld();

	if (!world)
		return names;

	const TArray<ULevelStreaming*>& levels = world->GetStreamingLevels();
	for (ULevelStreaming* level : levels)
	{
		names.Add(level->PackageNameToLoad);
	}
	return names;
}
