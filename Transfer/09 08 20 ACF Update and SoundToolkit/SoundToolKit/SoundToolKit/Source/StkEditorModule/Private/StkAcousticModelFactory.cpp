//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#include "StkAcousticModelFactory.h"
#include "StkAcousticModel.h"
#include "IStkEditorModule.h"

UStkAcousticModelFactory::UStkAcousticModelFactory()
{
	bCreateNew = true;
	bEditAfterNew = true;
	bEditorImport = false;
	SupportedClass = UStkAcousticModel::StaticClass();
}

UObject* UStkAcousticModelFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UStkAcousticModel>(InParent, Class, Name, Flags);
}

uint32 UStkAcousticModelFactory::GetMenuCategories() const
{
	return SoundToolKit::IStkEditorModule::Get().GetSoundToolKitAssetsCategoryBit();
}
