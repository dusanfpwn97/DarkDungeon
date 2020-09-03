// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#include "MusicManager.h"
#include "Logging.h"

#include "Modules/ModuleManager.h"

#define LOCTEXT_NAMESPACE "FMusicManager"

void FMusicManager::StartupModule()
{
}

void FMusicManager::ShutdownModule()
{
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMusicManager, MusicManager);