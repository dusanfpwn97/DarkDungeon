//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#include "StkOcclusionSourceSettingsFactory.h"
#include "StkCommon.h"
#include "StkOcclusionSourceSettings.h"
#include "IStkEditorModule.h"

namespace SoundToolKit
{
	uint32 FAssetTypeActions_StkOcclusionSourceSettings::GetCategories()
	{
		return EAssetTypeCategories::Sounds;
	}

	FText FAssetTypeActions_StkOcclusionSourceSettings::GetName() const
	{
		return NSLOCTEXT("AssetTypeActions", "FAssetTypeActions_StkOcclusionSourceSettings", "SoundToolKit Occlusion Settings");
	}

	UClass* FAssetTypeActions_StkOcclusionSourceSettings::GetSupportedClass() const
	{
		return UStkOcclusionSourceSettings::StaticClass();
	}

	FColor FAssetTypeActions_StkOcclusionSourceSettings::GetTypeColor() const
	{
		return FColor(192, 64, 64);
	}
}

UStkOcclusionSourceSettingsFactory::UStkOcclusionSourceSettingsFactory()
{
	SupportedClass = UStkOcclusionSourceSettings::StaticClass();

	bCreateNew = true;
	bEditorImport = false;
	bEditAfterNew = true;
}

UObject* UStkOcclusionSourceSettingsFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext*)
{
	return NewObject<UStkOcclusionSourceSettings>(InParent, Class, Name, Flags);
}

uint32 UStkOcclusionSourceSettingsFactory::GetMenuCategories() const
{
	return EAssetTypeCategories::Sounds | SoundToolKit::IStkEditorModule::Get().GetSoundToolKitAssetsCategoryBit();
}
