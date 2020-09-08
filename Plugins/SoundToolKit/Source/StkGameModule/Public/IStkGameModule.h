//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#pragma once

THIRD_PARTY_INCLUDES_START
#include <stk/UniqueResource.h>
#include <stk_ex/diagnostics/ISoundPathsCache.h>
THIRD_PARTY_INCLUDES_END

#include "Modules/ModuleManager.h"

/// <summary>
///	Interface of the core STK plugin module.
/// </summary>
class IStkGameModule : public IModuleInterface
{
public:
	/// <summary>
	/// Loads this module ensuring it exists.
	/// </summary>
	/// <returns>Interface of existing instance of this module</returns>
	static IStkGameModule& Get()
	{
		return FModuleManager::LoadModuleChecked<IStkGameModule>("StkGameModule");
	}

	/// <summary>
	/// Checks whether the module is loaded.
	/// </summary>
	/// <returns>True if the module is loaded</returns>
	static bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("StkGameModule");
	}

	/// <returns>Interface used to query for the diagnositcs data.</returns>
	virtual stk::UniqueResource<stk_ex::diagnostics::ISoundPathsCache> CreateSoundPathsCache() = 0;

	/// <summary>
	/// Updates sound paths, which connect sound sources with receiver through variety of acoustic phenomena,
	/// like reflection, transmission, or diffraction.
	/// </summary>
	virtual void ComputeSoundFrame() = 0;

	/// <summary>
	/// Propagates all the commands issued to the engine.
	/// </summary>
	virtual void Flush() = 0;

	/// <summary>
	/// Propagates all the commands issued to the engine and waits until all of them are executed.
	/// </summary>
	virtual void Finish() = 0;

	/// <returns>The number of sound sources that are currently processed by SoundToolKit engine.</returns>
	virtual int32 GetSoundSourcesNum() = 0;
};
