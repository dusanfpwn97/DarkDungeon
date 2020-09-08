//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#include "StkReverbSourceSettingsFactory.h"
#include "StkCommon.h"
#include "StkReverbSourceSettings.h"
#include "IStkEditorModule.h"

namespace SoundToolKit
{
	uint32 FAssetTypeActions_StkReverbSourceSettings::GetCategories()
	{
		return EAssetTypeCategories::Sounds;
	}

	FText FAssetTypeActions_StkReverbSourceSettings::GetName() const
	{
		return NSLOCTEXT("AssetTypeActions", "FAssetTypeActions_StkReverbSourceSettings", "SoundToolKit Reverb Settings");
	}

	UClass* FAssetTypeActions_StkReverbSourceSettings::GetSupportedClass() const
	{
		return UStkReverbSourceSettings::StaticClass();
	}

	FColor FAssetTypeActions_StkReverbSourceSettings::GetTypeColor() const
	{
		return FColor(192, 64, 64);
	}
}

UStkReverbSourceSettingsFactory::UStkReverbSourceSettingsFactory()
{
	SupportedClass = UStkReverbSourceSettings::StaticClass();

	bCreateNew = true;
	bEditorImport = false;
	bEditAfterNew = true;
}

UObject* UStkReverbSourceSettingsFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext*)
{
	return NewObject<UStkReverbSourceSettings>(InParent, Class, Name, Flags);
}

uint32 UStkReverbSourceSettingsFactory::GetMenuCategories() const
{
	return EAssetTypeCategories::Sounds | SoundToolKit::IStkEditorModule::Get().GetSoundToolKitAssetsCategoryBit();
}
