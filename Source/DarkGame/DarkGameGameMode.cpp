// Copyright Epic Games, Inc. All Rights Reserved.

#include "DarkGameGameMode.h"
#include "DarkGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADarkGameGameMode::ADarkGameGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Core/BP_PlayerWizard"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
