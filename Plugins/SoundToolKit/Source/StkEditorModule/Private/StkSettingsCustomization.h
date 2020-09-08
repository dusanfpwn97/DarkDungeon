//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#pragma once

#include "StkSettings.h"

#include "IDetailCustomization.h"

namespace SoundToolKit
{
	class FStkSettingsCustomization : public IDetailCustomization
	{
	public:
		static TSharedRef<IDetailCustomization> MakeInstance();

		// IDetailCustomization interface
		virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;
		// End of IDetailCustomization interface

	private:
		TSharedRef<SWidget> CreateSettingEditorWidget(FStkSetting& Setting);

		TSharedRef<SWidget> CreateCheckBoxWidget(FStkSetting& Setting);
		TSharedRef<SWidget> CreateComboBoxWidget(FStkSetting& Setting);
		TSharedRef<SWidget> CreateIntegerEntryBoxWidget(FStkSetting& Setting);
		TSharedRef<SWidget> CreateFloatEntryBoxWidget(FStkSetting& Setting);
		TSharedRef<SWidget> CreateListOfIntegerEntryWidget(FStkSetting& Setting);

		FStkSetting* GetSettingByName(const FString& SettingName);

	private:
		TWeakObjectPtr<class UStkSettings> StkSettings;

		TMap<FString, TArray<TSharedPtr<FString>>> EnumerationSettingsOptions;
	};
}
