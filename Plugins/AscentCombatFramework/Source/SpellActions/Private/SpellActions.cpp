// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#include "SpellActions.h"
#include "Logging.h"

#include "Modules/ModuleManager.h"

#define LOCTEXT_NAMESPACE "FSpellActions"

void FSpellActions::StartupModule()
{
}

void FSpellActions::ShutdownModule()
{
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSpellActions, SpellActions);