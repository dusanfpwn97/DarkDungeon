//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#pragma once

#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"
#include "AssetTypeCategories.h"

namespace SoundToolKit
{
	/// <summary>
	///	SoundToolKit plugin module responsible for Editor related features.
	/// </summary>
	class IStkEditorModule : public IModuleInterface
	{
	public:
		static inline IStkEditorModule& Get()
		{
			return FModuleManager::LoadModuleChecked<IStkEditorModule>("StkEditorModule");
		}

		static inline bool IsAvailable()
		{
			return FModuleManager::Get().IsModuleLoaded("StkEditorModule");
		}

		virtual EAssetTypeCategories::Type GetSoundToolKitAssetsCategoryBit() = 0;
	};
}
