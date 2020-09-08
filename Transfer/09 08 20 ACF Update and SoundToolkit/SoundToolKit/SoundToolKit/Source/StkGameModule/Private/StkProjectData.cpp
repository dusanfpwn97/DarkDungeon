//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#include "StkProjectData.h"

#include "Misc/Paths.h"
#include "Misc/PackageName.h"
#include "AssetRegistryModule.h"

namespace
{
	const FString AssetName{ TEXT("StkProjectData") };
	const FString AssetPath{ TEXT("/Game") };
}

UStkProjectData* UStkProjectData::StkProjectData;

void UStkProjectData::Init()
{
	FString ProjectDataPath = UStkProjectData::StaticClass()->GetName()
		+ TEXT("'") + FPaths::Combine(AssetPath, AssetName) + TEXT(".") + AssetName + TEXT("'");
	FStringAssetReference ProjectDataRef(ProjectDataPath);
	StkProjectData = Cast<UStkProjectData>(ProjectDataRef.TryLoad());

	if (StkProjectData)
	{
		StkProjectData->AddToRoot();
		StkProjectData->PostLoad();
	}
}

void UStkProjectData::Create()
{
	const FString LongPackageName = FPaths::Combine(AssetPath, AssetName);

	UPackage* Package = CreatePackage(nullptr, *LongPackageName);
	Package->FullyLoad();
	Package->MarkPackageDirty();

	UStkProjectData* StkProjectDataAsset = NewObject<UStkProjectData>(Package, *AssetName, RF_Public | RF_Standalone);

	FAssetRegistryModule::AssetCreated(StkProjectDataAsset);
	StkProjectDataAsset->MarkPackageDirty();

	const FString PackageFilename = FPackageName::LongPackageNameToFilename(LongPackageName, FPackageName::GetAssetPackageExtension());
	UPackage::SavePackage(Package, StkProjectDataAsset, RF_Public | RF_Standalone, *PackageFilename);
}

UStkProjectData* UStkProjectData::Get()
{
	return StkProjectData;
}
