//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#include "StkMaterialAssetsGenerator.h"
#include "StkGameModule.h"
#include "StkAcousticMaterial.h"
#include "StkCommon.h"
#include "Misc/Paths.h"
#include "AssetRegistryModule.h"
#include "HAL/FileManager.h"
#include "Misc/FileHelper.h"

THIRD_PARTY_INCLUDES_START
#include <stk_ex/scene/MaterialsSerializer.h>
THIRD_PARTY_INCLUDES_END

namespace SoundToolKit
{
	void StkMaterialAssetsGenerator::Generate()
	{
		GenerateAcousticMaterialAssetsFromDir(GetMaterialsDataDirectory());
	}

	void StkMaterialAssetsGenerator::GenerateAcousticMaterialAssetsFromDir(const FString& SourceDirectory)
	{
		IFileManager& FileManager = IFileManager::Get();
		const FString DestinationDirectory = GetMaterialsContentDirectory();

		if (!FileManager.DirectoryExists(*SourceDirectory))
		{
			return;
		}
		TArray<FString> ResourceMaterialFiles = GetResourceMaterialListFromDirectory(SourceDirectory);

		TArray<FString> ContentMaterialFiles;
		if (!FileManager.DirectoryExists(*DestinationDirectory))
		{
			FileManager.MakeDirectory(*DestinationDirectory, true);
			CreateMaterialAssets(ResourceMaterialFiles);
		}
	}

	TArray<FString> StkMaterialAssetsGenerator::GetResourceMaterialListFromDirectory(const FString& Directory)
	{
		TArray<FString> MaterialList;

		IFileManager::Get().FindFilesRecursive(MaterialList, *Directory, TEXT("*.json"), true, false);

		return MaterialList;
	}

	TArray<FString> StkMaterialAssetsGenerator::GetContentMaterialListFromDirectory(const FString& Directory)
	{
		TArray<FString> MaterialList;

		const FString Query = FPaths::Combine(Directory, TEXT("*") + FPackageName::GetAssetPackageExtension());
		IFileManager::Get().FindFiles(MaterialList, *Query, true, false);
		for (FString& File : MaterialList)
		{
			File = FPaths::GetBaseFilename(File);
		}

		return MaterialList;
	}

	void StkMaterialAssetsGenerator::CreateMaterialAssets(const TArray<FString>& MaterialJsonPaths)
	{
		const FString DestinationDirectory = GetMaterialsContentDirectory();

		for (const FString& JsonPath : MaterialJsonPaths)
		{
			SaveMaterialAsAsset(JsonPath, DestinationDirectory);
		}
	}

	void StkMaterialAssetsGenerator::SaveMaterialAsAsset(const FString& JsonPath, const FString& DestinationDirectory)
	{
		using SoundToolKit::Utils::ConvertSnakeCaseToCamelCase;
		const FString MaterialName = ConvertSnakeCaseToCamelCase(FPaths::GetBaseFilename(JsonPath));
		const FString LongPackageName = FPaths::Combine(TEXT("/SoundToolKit"), TEXT("Materials"), MaterialName);

		// create a package to save the asset
		UPackage* Package = CreatePackage(nullptr, *LongPackageName);
		Package->FullyLoad();
		Package->MarkPackageDirty();

		// create the asset and mark it so it's not GCed
		UStkAcousticMaterial* MaterialAsset = NewObject<UStkAcousticMaterial>(Package, *MaterialName, RF_Public | RF_Standalone);

		// load the material from json path and use it to set the Material Asset's coefficients
		MaterialAsset->LoadMaterial(JsonPath);
		MaterialAsset->InitializeControls();

		// notify the asset registry and mark the asset dirty so it can be saved
		FAssetRegistryModule::AssetCreated(MaterialAsset);
		MaterialAsset->MarkPackageDirty();

		// save as .uasset file
		const FString PackageFilename = FPackageName::LongPackageNameToFilename(LongPackageName, FPackageName::GetAssetPackageExtension());
		UPackage::SavePackage(Package, MaterialAsset, RF_Public | RF_Standalone, *PackageFilename);
	}

	FString StkMaterialAssetsGenerator::GetMaterialsDataDirectory()
	{
		using SoundToolKit::Utils::GetPluginPath;
		static FString MaterialsDataDirectory = FPaths::Combine(GetPluginPath(), TEXT("Resources"), TEXT("assets"), TEXT("materials"));
		return MaterialsDataDirectory;
	}

	FString StkMaterialAssetsGenerator::GetMaterialsContentDirectory()
	{
		using SoundToolKit::Utils::GetContentPath;
		static FString MaterialsContentDirectory = FPaths::Combine(GetContentPath(), TEXT("Materials"));
		return MaterialsContentDirectory;
	}
}
