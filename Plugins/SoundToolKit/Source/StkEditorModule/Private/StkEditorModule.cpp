//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#include "StkCommon.h"
#include "IStkEditorModule.h"
#include "StkExtensions.h"
#include "StkSettings.h"
#include "StkDiagnostics.h"
#include "StkScene.h"
#include "StkProjectData.h"
#include "StkSpatializationSettingsCustomization.h"
#include "StkAcousticMaterialCustomization.h"
#include "StkSettingsCustomization.h"
#include "StkSceneCustomization.h"
#include "StkObjectCustomization.h"
#include "StkProjectDataCustomization.h"

#include "PropertyEditorModule.h"
#include "IPlacementModeModule.h"
#include "ISettingsModule.h"
#include "AssetToolsModule.h"
#include "Landscape.h"
#include "AssetRegistryModule.h"

#define LOCTEXT_NAMESPACE "StkEditorModule"

namespace
{
	void RegisterPlacementModeExtensions()
	{
		FPlacementCategoryInfo Info(
			LOCTEXT("SoundToolKitCategoryName", "SoundToolKit"),
			"SoundToolKit",
			TEXT("PMSoundToolKit"));

		IPlacementModeModule::Get().RegisterPlacementCategory(Info);

		IPlacementModeModule::Get().RegisterPlaceableItem(Info.UniqueHandle, MakeShareable(
			new FPlaceableItem(nullptr, FAssetData(AStkScene::StaticClass()))));
		IPlacementModeModule::Get().RegisterPlaceableItem(Info.UniqueHandle, MakeShareable(
			new FPlaceableItem(nullptr, FAssetData(AStkExtensions::StaticClass()))));
		IPlacementModeModule::Get().RegisterPlaceableItem(Info.UniqueHandle, MakeShareable(
			new FPlaceableItem(nullptr, FAssetData(AStkDiagnostics::StaticClass()))));
	}

	void UnregisterPlacementModeExtensions()
	{
		if (IPlacementModeModule::IsAvailable())
		{
			IPlacementModeModule::Get().UnregisterPlacementCategory("SoundToolKit");
		}
	}

	EAssetTypeCategories::Type RegisterAssetsCategory()
	{
		IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
		return AssetTools.RegisterAdvancedAssetCategory(FName(TEXT("SoundToolKit")), LOCTEXT("StkAssetCategory", "SoundToolKit"));
	}
}

namespace SoundToolKit
{
	class FStkEditorModule : public IStkEditorModule
	{
	public:
		// IModuleInterface implementation
		virtual void StartupModule() override;
		virtual void ShutdownModule() override;
		
		EAssetTypeCategories::Type GetSoundToolKitAssetsCategoryBit() override
		{
			return SoundToolKitAssetsCategoryBit;
		}

	private:
		EAssetTypeCategories::Type SoundToolKitAssetsCategoryBit;
	};
}

IMPLEMENT_MODULE(SoundToolKit::FStkEditorModule, StkEditorModule)

namespace SoundToolKit
{
	void FStkEditorModule::StartupModule()
	{
		// Register StkSettings
		ISettingsModule& SettingsModule = FModuleManager::Get().GetModuleChecked<ISettingsModule>("Settings");
		SettingsModule.RegisterSettings("Project", "Plugins", "SoundToolKit", LOCTEXT("SoundToolKitSettingsName", "SoundToolKit"),
			LOCTEXT("SoundToolKitSettingsDescription", "Configure SoundToolKit settings"), GetMutableDefault<UStkSettings>());

		FPropertyEditorModule& PropertyModule = FModuleManager::Get().GetModuleChecked<FPropertyEditorModule>("PropertyEditor");

		// Register StkSettings details customization 
		PropertyModule.RegisterCustomClassLayout("StkSettings",
			FOnGetDetailCustomizationInstance::CreateStatic(&FStkSettingsCustomization::MakeInstance));

		// Register StkSpatializationSourceSettings details customization 
		PropertyModule.RegisterCustomClassLayout("StkSpatializationSourceSettings",
			FOnGetDetailCustomizationInstance::CreateStatic(&FStkSpatializationSettingsCustomization::MakeInstance));

		// Register AcousticMaterial objects details customization 
		PropertyModule.RegisterCustomClassLayout("StkAcousticMaterial",
			FOnGetDetailCustomizationInstance::CreateStatic(&FStkAcousticMaterialCustomization::MakeInstance));

		// Register Scene details customization 
		PropertyModule.RegisterCustomClassLayout("StkScene",
			FOnGetDetailCustomizationInstance::CreateStatic(&FStkSceneCustomization::MakeInstance));

		// Register Landscape objects details customization 
		PropertyModule.RegisterCustomClassLayout("Landscape",
			FOnGetDetailCustomizationInstance::CreateStatic(&FStkObjectCustomization<ALandscape>::MakeInstance));

		// Register StaticMeshComponent objects details customization 
		PropertyModule.RegisterCustomClassLayout("StaticMeshComponent",
			FOnGetDetailCustomizationInstance::CreateStatic(&FStkObjectCustomization<UStaticMeshComponent>::MakeInstance));

		// Register StkProjectData details customization 
		PropertyModule.RegisterCustomClassLayout("StkProjectData",
			FOnGetDetailCustomizationInstance::CreateStatic(&FStkProjectDataCustomization::MakeInstance));

		PropertyModule.NotifyCustomizationModuleChanged();

		RegisterPlacementModeExtensions();
		SoundToolKitAssetsCategoryBit = RegisterAssetsCategory();

		if (!UStkProjectData::Get())
		{
			UStkProjectData::Create();
			UStkProjectData::Init();
		}
	}

	void FStkEditorModule::ShutdownModule()
	{
		// Unregister StkSettings
		ISettingsModule& SettingsModule = FModuleManager::Get().GetModuleChecked<ISettingsModule>("Settings");
		SettingsModule.UnregisterSettings("Project", "Plugins", "SoundToolKit");

		// Unregister StkExtensions details customization 
		FPropertyEditorModule& PropertyModule = FModuleManager::Get().GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
		PropertyModule.UnregisterCustomClassLayout("StkExtensions");

		UnregisterPlacementModeExtensions();
	}
}

#undef LOCTEXT_NAMESPACE
