//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#pragma once

#include "Logging/LogMacros.h"

STKGAMEMODULE_API DECLARE_LOG_CATEGORY_EXTERN(LogSoundToolKit, Log, All);

// Used to log to LogSoundToolKit category.
#define STK_LOG(Verbosity, Format, ...) UE_LOG(LogSoundToolKit, Verbosity, Format, ##__VA_ARGS__)

// Checks if given verbosity of LogSoundToolKit will be printed.
#define STK_LOG_ACTIVE(Verbosity) UE_LOG_ACTIVE(LogSoundToolKit, Verbosity)

// Checks if a given expression is true and if it's not, prints to log.
// Fatal verbosity and false expression will stop the execution.
// If Verbose verbosity is active for LogSoundToolKit, file, line and function of the check will be printed as well. 
#define STK_CHECK(Expression, Verbosity, Format, ...) \
if (STK_LOG_ACTIVE(Verbosity) && !(Expression)) \
{ \
	if (STK_LOG_ACTIVE(Verbose)) \
	{ \
		STK_LOG(Verbose, TEXT("%s(%d): %s"), *FString(__FILE__), __LINE__, *FString(__FUNCTION__)); \
	} \
	STK_LOG(Verbosity, Format, ##__VA_ARGS__); \
}
