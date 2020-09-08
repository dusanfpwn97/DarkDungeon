//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#pragma once

namespace SoundToolKit
{
	class StkMaterialAssetsGenerator
	{
	public:
		/// <summary>
		/// Creates StkAcousticMaterial assets (.uasset files), based on .json STK material files.
		/// </summary>
		static void Generate();

	private:
		/// <summary>
		/// Creates StkAcousticMaterial assets (.uasset files), based on .json STK material files and directories located in SourceDirectory.
		/// Directory hierarchy of elements in SourceDirectory is preserved.
		/// The method recursively calls itself with each directory inside SourceDirectory as a parameter.
		/// </summary>
		/// <param name="SourceDirectory">Directory relative to Resources/assets/materials</param>
		static void GenerateAcousticMaterialAssetsFromDir(const FString& SourceDirectory);
		static TArray<FString> GetResourceMaterialListFromDirectory(const FString& Directory);
		static TArray<FString> GetContentMaterialListFromDirectory(const FString& Directory);
		static void CreateMaterialAssets(const TArray<FString>& MaterialJsonPaths);
		static void SaveMaterialAsAsset(const FString& JsonPath, const FString& DestinationDirectory);
		/// <summary>
		/// Used to get relative path to Resources/assets/materials directory, which contains all material files.
		/// </summary>
		/// <returns>Relative path to materials directory</returns>
		static FString GetMaterialsDataDirectory();

		/// <summary>
		/// Used to get relative path to material dir in plugin's Content directory, where all StkAcousticMaterial assets should be stored.
		/// </summary>
		/// <returns>Relative path to materials directory inside plugins Content directory</returns>
		static FString GetMaterialsContentDirectory();
	};
}
