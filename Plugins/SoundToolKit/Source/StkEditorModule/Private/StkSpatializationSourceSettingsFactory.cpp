//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#include "StkSpatializationSourceSettingsFactory.h"
#include "StkCommon.h"
#include "StkSpatializationSourceSettings.h"
#include "IStkEditorModule.h"

namespace SoundToolKit
{
	uint32 FAssetTypeActions_StkSpatializationSourceSettings::GetCategories()
	{
		return EAssetTypeCategories::Sounds;
	}

	FText FAssetTypeActions_StkSpatializationSourceSettings::GetName() const
	{
		return NSLOCTEXT("AssetTypeActions", "FAssetTypeActions_StkSpatializationSourceSettings", "SoundToolKit Spatialization Settings");
	}

	UClass* FAssetTypeActions_StkSpatializationSourceSettings::GetSupportedClass() const
	{
		return UStkSpatializationSourceSettings::StaticClass();
	}

	FColor FAssetTypeActions_StkSpatializationSourceSettings::GetTypeColor() const
	{
		return FColor(192, 64, 64);
	}
}

UStkSpatializationSourceSettingsFactory::UStkSpatializationSourceSettingsFactory()
{
	SupportedClass = UStkSpatializationSourceSettings::StaticClass();

	bCreateNew = true;
	bEditorImport = false;
	bEditAfterNew = true;
}

UObject* UStkSpatializationSourceSettingsFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext*)
{
	return NewObject<UStkSpatializationSourceSettings>(InParent, Class, Name, Flags);
}

uint32 UStkSpatializationSourceSettingsFactory::GetMenuCategories() const
{
	return EAssetTypeCategories::Sounds | SoundToolKit::IStkEditorModule::Get().GetSoundToolKitAssetsCategoryBit();
}
