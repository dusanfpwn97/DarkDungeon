//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#include "StkSettingsCustomization.h"
#include "StkCommon.h"

THIRD_PARTY_INCLUDES_START
#include <stk/ISetting.h>
THIRD_PARTY_INCLUDES_END

#include "DetailLayoutBuilder.h"
#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"
#include "Widgets/Layout/SGridPanel.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Input/SCheckBox.h"
#include "Widgets/Input/STextComboBox.h"
#include "Widgets/Input/SNumericEntryBox.h"

namespace
{
	FString SettingTypeToString(EStkSettingType SettingType)
	{
		switch (SettingType)
		{
		case EStkSettingType::StkSettingType_Boolean:
			return TEXT("Boolean");
		case EStkSettingType::StkSettingType_Enumeration:
			return TEXT("Enumeration");
		case EStkSettingType::StkSettingType_Integer:
			return TEXT("Integer");
		case EStkSettingType::StkSettingType_Float:
			return TEXT("Float");
		case EStkSettingType::StkSettingType_ListOfIntegers:
			return TEXT("List Of Integers");
		case EStkSettingType::StkSettingType_ListOfFloats:
			return TEXT("List Of Floats");
		default:
			return TEXT("Invalid Type");
		}
	}
}

namespace SoundToolKit
{
	TSharedRef<IDetailCustomization> FStkSettingsCustomization::MakeInstance()
	{
		return MakeShareable(new FStkSettingsCustomization);
	}

	void FStkSettingsCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
	{
		const TArray<TWeakObjectPtr<UObject>>& SelectedObjects = DetailBuilder.GetSelectedObjects();
		for (const TWeakObjectPtr<UObject>& Object : SelectedObjects)
		{
			if (Object.IsValid())
			{
				UStkSettings* StkSettingsPtr = Cast<UStkSettings>(Object.Get());
				if (StkSettingsPtr)
				{
					StkSettings = StkSettingsPtr;
					break;
				}
			}
		}

		if (StkSettings.IsValid())
		{
			TArray<FStkSetting> Settings = StkSettings->GetSettings();

			TSet<FString> Categories;
			for (FStkSetting Setting : Settings)
			{
				Categories.Add(Setting.Category);
			}
			Categories.Sort([](const FString& A, const FString& B) { return A < B; });

			for (FString Category : Categories)
			{
				IDetailCategoryBuilder& SettingsCategory = DetailBuilder.EditCategory(*Category);

				for (FStkSetting Setting : Settings)
				{
					if (Setting.Category != Category)
					{
						continue;
					}

					SettingsCategory.AddCustomRow(FText::FromString(Setting.Name))
					.NameContent()
					[
						SNew(STextBlock)
						.Text(FText::FromString(Setting.Name))
						.ToolTipText(FText::FromString(Setting.Description))
						.Font(IDetailLayoutBuilder::GetDetailFont())
					]
					.ValueContent()
					[
						SNew(SGridPanel)
						+ SGridPanel::Slot(0, 0)
						.HAlign(EHorizontalAlignment::HAlign_Fill)
						[
							SNew(STextBlock)
							.Text(FText::FromString(TEXT("Type")))
							.Font(IDetailLayoutBuilder::GetDetailFont())
						]
						+ SGridPanel::Slot(1, 0)
						.HAlign(EHorizontalAlignment::HAlign_Fill)
						.Padding(10.0f, 0.0f)
						[
							SNew(STextBlock)
							.Text(FText::FromString(SettingTypeToString(Setting.Type)))
							.Font(IDetailLayoutBuilder::GetDetailFont())
						]
						+ SGridPanel::Slot(0, 1)
						.HAlign(EHorizontalAlignment::HAlign_Fill)
						[
							SNew(STextBlock)
							.Text(FText::FromString(TEXT("Default Value")))
							.Font(IDetailLayoutBuilder::GetDetailFont())
						]
						+ SGridPanel::Slot(1, 1)
						.HAlign(EHorizontalAlignment::HAlign_Fill)
						.Padding(10.0f, 0.0f)
						[
							SNew(STextBlock)
							.Text(FText::FromString(Setting.DefaultValue))
							.Font(IDetailLayoutBuilder::GetDetailFont())
						]
						+ SGridPanel::Slot(0, 2)
						.HAlign(EHorizontalAlignment::HAlign_Fill)
						[
							SNew(STextBlock)
							.Text(FText::FromString(TEXT("Current Value")))
							.Font(IDetailLayoutBuilder::GetDetailFont())
						]
						+ SGridPanel::Slot(1, 2)
						.HAlign(EHorizontalAlignment::HAlign_Fill)
						.Padding(10.0f, 0.0f)
						[
							CreateSettingEditorWidget(Setting)
						]
					];
				}
			}
		}
	}

	TSharedRef<SWidget> FStkSettingsCustomization::CreateSettingEditorWidget(FStkSetting& Setting)
	{
		switch (Setting.Type)
		{
		case EStkSettingType::StkSettingType_Boolean:
			return CreateCheckBoxWidget(Setting);
		case EStkSettingType::StkSettingType_Enumeration:
			return CreateComboBoxWidget(Setting);
		case EStkSettingType::StkSettingType_Integer:
			return CreateIntegerEntryBoxWidget(Setting);
		case EStkSettingType::StkSettingType_Float:
			return CreateFloatEntryBoxWidget(Setting);
		case EStkSettingType::StkSettingType_ListOfIntegers:
			return CreateListOfIntegerEntryWidget(Setting);
		case EStkSettingType::StkSettingType_ListOfFloats:
		default:
			STK_LOG(Fatal, TEXT("Unimplemented type of SoundToolKit setting."));
			return SNew(STextBlock);
		}
	}

	TSharedRef<SWidget> FStkSettingsCustomization::CreateCheckBoxWidget(FStkSetting& Setting)
	{
		return SNew(SCheckBox)
			.OnCheckStateChanged_Lambda([this, SettingName = Setting.Name](ECheckBoxState CheckBoxState)
			{
				if (FStkSetting* TargetSetting = GetSettingByName(SettingName))
				{
					TargetSetting->CurrentValue = CheckBoxState == ECheckBoxState::Checked ? TEXT("true") : TEXT("false");
					TargetSetting->Update();
					StkSettings->SaveConfig();
				}
			})
			.IsChecked(Setting.CurrentValue.ToBool() ? ECheckBoxState::Checked : ECheckBoxState::Unchecked)
			.ToolTipText(FText::FromString(Setting.Description));
	}

	TSharedRef<SWidget> FStkSettingsCustomization::CreateComboBoxWidget(FStkSetting& Setting)
	{
		FString AllowedValues = Setting.AllowedValues;
		AllowedValues.RemoveFromStart(TEXT("{"));
		AllowedValues.RemoveFromEnd(TEXT("}"));
		TArray<FString> EnumOptionsNames;
		AllowedValues.ParseIntoArray(EnumOptionsNames, TEXT(", "));

		TArray<TSharedPtr<FString>>& EnumOptions = EnumerationSettingsOptions.Emplace(Setting.Name, TArray<TSharedPtr<FString>>{});
		for (FString EnumOptionName : EnumOptionsNames)
		{
			EnumOptions.Add(MakeShareable(new FString(EnumOptionName)));
		}

		return SNew(STextComboBox)
			.OnSelectionChanged_Lambda([this, SettingName = Setting.Name](TSharedPtr<FString> ItemSelected, ESelectInfo::Type)
			{
				if (FStkSetting* TargetSetting = GetSettingByName(SettingName))
				{
					TargetSetting->CurrentValue = *ItemSelected;
					TargetSetting->Update();
					StkSettings->SaveConfig();
				}
			})
			.OptionsSource(&EnumOptions)
			.InitiallySelectedItem(*EnumOptions.FindByPredicate([Setting](TSharedPtr<FString> Option) { return *Option == Setting.CurrentValue; }))
			.ToolTipText(FText::FromString(Setting.Description))
			.Font(IDetailLayoutBuilder::GetDetailFont());
	}

	TSharedRef<SWidget> FStkSettingsCustomization::CreateIntegerEntryBoxWidget(FStkSetting& Setting)
	{
		FString AllowedValues = Setting.AllowedValues;
		AllowedValues.RemoveFromStart(TEXT("["));
		AllowedValues.RemoveFromEnd(TEXT("]"));
		TArray<FString> MinMaxValues;
		AllowedValues.ParseIntoArray(MinMaxValues, TEXT(", "));

		int32 MinValue = FCString::Atoi(*MinMaxValues[0]);
		int32 MaxValue = FCString::Atoi(*MinMaxValues[1]);

		return SNew(SBox)
			.HeightOverride(18)
			[
				SNew(SNumericEntryBox<int32>)
				.Value_Lambda([this, SettingName = Setting.Name]()->TOptional<int32>
				{
					if (FStkSetting* TargetSetting = GetSettingByName(SettingName))
					{
						return FCString::Atoi(*TargetSetting->CurrentValue);
					}
					return TOptional<int32>();
				})
					.OnValueChanged_Lambda([this, SettingName = Setting.Name](int32 Value)
				{
					if (FStkSetting* TargetSetting = GetSettingByName(SettingName))
					{
						TargetSetting->CurrentValue = FString::FromInt(Value);
						TargetSetting->Update();
						StkSettings->SaveConfig();
					}
				})
				.MinValue(MinValue)
				.MaxValue(MaxValue)
				.MinSliderValue(MinValue)
				.MaxSliderValue(MaxValue)
				.AllowSpin(true)
				.ToolTipText(FText::FromString(Setting.Description))
				.Font(IDetailLayoutBuilder::GetDetailFont())
			];
	}

	TSharedRef<SWidget> FStkSettingsCustomization::CreateFloatEntryBoxWidget(FStkSetting& Setting)
	{
		FString AllowedValues = Setting.AllowedValues;
		bool bLeftClosed = AllowedValues.StartsWith(TEXT("["));
		bool bRightClosed = AllowedValues.EndsWith(TEXT("]"));
		
		AllowedValues.RemoveFromStart(bLeftClosed ? TEXT("[") : TEXT("("));
		AllowedValues.RemoveFromEnd(bRightClosed ? TEXT("]") : TEXT(")"));
		TArray<FString> MinMaxValues;
		AllowedValues.ParseIntoArray(MinMaxValues, TEXT(", "));

		float MinValue = FCString::Atof(*MinMaxValues[0]);
		float MaxValue = FCString::Atof(*MinMaxValues[1]);

		if (!bLeftClosed)
		{
			MinValue += TNumericLimits<float>::Min();
		}
		if (!bRightClosed)
		{
			MaxValue -= TNumericLimits<float>::Min();
		}

		return SNew(SBox)
			.HeightOverride(18)
			[
				SNew(SNumericEntryBox<float>)
				.Value_Lambda([this, SettingName = Setting.Name]()->TOptional<float>
				{
					if (FStkSetting* TargetSetting = GetSettingByName(SettingName))
					{
						return FCString::Atof(*TargetSetting->CurrentValue);
					}
					return TOptional<float>();
				})
				.OnValueChanged_Lambda([this, SettingName = Setting.Name](float Value)
				{
					if (FStkSetting* TargetSetting = GetSettingByName(SettingName))
					{
						TargetSetting->CurrentValue = FString::SanitizeFloat(Value);
						TargetSetting->Update();
						StkSettings->SaveConfig();
					}
				})
				.MinValue(MinValue)
				.MaxValue(MaxValue)
				.MinSliderValue(MinValue)
				.MaxSliderValue(MaxValue)
				.AllowSpin(true)
				.ToolTipText(FText::FromString(Setting.Description))
				.Font(IDetailLayoutBuilder::GetDetailFont())
			];
	}

	TSharedRef<SWidget> FStkSettingsCustomization::CreateListOfIntegerEntryWidget(FStkSetting& Setting)
	{
		TArray<FString> CurrentValues;
		Setting.CurrentValue.ParseIntoArray(CurrentValues, TEXT(" "));

		FString AllowedValues = Setting.AllowedValues;
		AllowedValues.RemoveFromStart(TEXT("["));
		int32 CloseRangeIndex;
		AllowedValues.FindChar(TCHAR(']'), CloseRangeIndex);
		AllowedValues = AllowedValues.Left(CloseRangeIndex);

		TArray<FString> MinMaxValues;
		AllowedValues.ParseIntoArray(MinMaxValues, TEXT(", "));

		int32 MinValue = FCString::Atoi(*MinMaxValues[0]);
		int32 MaxValue = FCString::Atoi(*MinMaxValues[1]);

		TSharedRef<SGridPanel> GridPanel = SNew(SGridPanel);

		for (int32 InputElementIndex = 0; InputElementIndex < CurrentValues.Num(); ++InputElementIndex)
		{
			GridPanel->AddSlot(InputElementIndex, 0)
				.HAlign(EHorizontalAlignment::HAlign_Fill)
				.Padding(0.0f, 0.0f, 10.0f, 0.0f)
				[
					SNew(SBox)
					.HeightOverride(18)
					[
						SNew(SNumericEntryBox<int32>)
							.Value_Lambda([this, SettingName = Setting.Name, InputElementIndex]()->TOptional<int32>
							{
								if (FStkSetting* TargetSetting = GetSettingByName(SettingName))
								{
									TArray<FString> ListValues;
									TargetSetting->CurrentValue.ParseIntoArray(ListValues, TEXT(" "));

									return FCString::Atoi(*ListValues[InputElementIndex]);
								}
								return TOptional<int32>();
							})
							.OnValueChanged_Lambda([this, SettingName = Setting.Name, InputElementIndex](int32 Value)
							{
								if (FStkSetting* TargetSetting = GetSettingByName(SettingName))
								{
									TArray<FString> ListValues;
									TargetSetting->CurrentValue.ParseIntoArray(ListValues, TEXT(" "));
									ListValues[InputElementIndex] = FString::FromInt(Value);

									FString NewValue;
									for (FString ListValue : ListValues)
									{
										NewValue.Append(ListValue);
										NewValue.AppendChar(TCHAR(' '));
									}
									NewValue.RemoveFromEnd(TEXT(" "));

									TargetSetting->CurrentValue = NewValue;
									TargetSetting->Update();
									StkSettings->SaveConfig();
								}
							})
							.MinValue(MinValue)
							.MaxValue(MaxValue)
							.MinSliderValue(MinValue)
							.MaxSliderValue(MaxValue)
							.AllowSpin(true)
							.ToolTipText(FText::FromString(Setting.Description))
							.Font(IDetailLayoutBuilder::GetDetailFont())
							.MinDesiredValueWidth(28)
					]
				];
		}

		return GridPanel;
	}

	FStkSetting* FStkSettingsCustomization::GetSettingByName(const FString& SettingName)
	{
		return StkSettings->GetSettings().FindByPredicate([SettingName](const FStkSetting& Setting) { return Setting.Name == SettingName; });
	}
}
