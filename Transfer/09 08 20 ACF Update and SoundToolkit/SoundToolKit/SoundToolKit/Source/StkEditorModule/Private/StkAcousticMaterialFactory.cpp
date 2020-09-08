//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#include "StkAcousticMaterialFactory.h"
#include "StkAcousticMaterial.h"
#include "IStkEditorModule.h"

UStkAcousticMaterialFactory::UStkAcousticMaterialFactory()
{
	bCreateNew = true;
	bEditAfterNew = true;
	bEditorImport = false;
	SupportedClass = UStkAcousticMaterial::StaticClass();
}

UObject* UStkAcousticMaterialFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	auto Object = NewObject<UStkAcousticMaterial>(InParent, Class, Name, Flags);
	Object->SetCustom();
	return Object;
}

uint32 UStkAcousticMaterialFactory::GetMenuCategories() const
{
	return SoundToolKit::IStkEditorModule::Get().GetSoundToolKitAssetsCategoryBit();
}
