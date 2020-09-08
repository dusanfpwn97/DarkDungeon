//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#include "StkSettings.h"
#include "StkCommon.h"
#include "StkGameModule.h"

THIRD_PARTY_INCLUDES_START
#include <stk/ISetting.h>
#include <stk/IControl.h>
THIRD_PARTY_INCLUDES_END

#include "CoreGlobals.h"

namespace
{
	EStkSettingType ConvertType(stk::SettingType StkType)
	{
		switch (StkType)
		{
		case stk::SettingType::Boolean:
			return EStkSettingType::StkSettingType_Boolean;
		case stk::SettingType::Enumeration:
			return EStkSettingType::StkSettingType_Enumeration;
		case stk::SettingType::Integer:
			return EStkSettingType::StkSettingType_Integer;
		case stk::SettingType::Float:
			return EStkSettingType::StkSettingType_Float;
		case stk::SettingType::ListOfIntegers:
			return EStkSettingType::StkSettingType_ListOfIntegers;
		case stk::SettingType::ListOfFloats:
			return EStkSettingType::StkSettingType_ListOfFloats;
		default:
			return static_cast<EStkSettingType>(-1);
		}
	}
}

FStkSetting::FStkSetting()
	: StkParameter(nullptr)
{
}

FStkSetting::FStkSetting(
	stk::ISetting* Parameter,
	const FString& CategoryIn,
	const FString& NameIn,
	EStkSettingType TypeIn,
	const FString& AllowedValuesIn,
	const FString& DescriptionIn,
	const FString& DefaultValueIn,
	const FString& CurrentValueIn)
	: Category(CategoryIn)
	, Name(NameIn)
	, Type(TypeIn)
	, AllowedValues(AllowedValuesIn)
	, Description(DescriptionIn)
	, DefaultValue(DefaultValueIn)
	, CurrentValue(CurrentValueIn)
	, OldValue(CurrentValue)
	, StkParameter(Parameter)
{
}

bool FStkSetting::IsPendingUpdate()
{
	return CurrentValue != OldValue;
}

void FStkSetting::Update()
{
	if (StkParameter)
	{
		SoundToolKit::Utils::GetGameModule().GetCommandDispatcher().Enqueue([&StkParameter{ StkParameter }, Value{ CurrentValue }]
			{
				StkParameter->setValue(TCHAR_TO_ANSI(*Value));
			});
		SoundToolKit::Utils::GetGameModule().Flush();

		OldValue = CurrentValue;
	}
	else
	{
		STK_LOG(Error, TEXT("StkParameter %s is invalid."), *Name);
	}
}

UStkSettings::UStkSettings()
{
	StkGameModulePtr = &SoundToolKit::Utils::GetGameModule();
}

TArray<FStkSetting>& UStkSettings::GetSettings()
{
	return Settings;
}

void UStkSettings::PostInitProperties()
{
	ValidateSettings();

	Super::PostInitProperties();
}

void UStkSettings::ValidateSettings()
{
	TArray<FStkSetting> NewSettings;
	auto connection = StkGameModulePtr->GetAudio()->control().connectOnSettingAdded([&NewSettings, this](stk::ISetting& StkParameter, stk::StringView currentValue)
	{
		FStkSetting* SerializedParameter = Settings.FindByPredicate([&StkParameter](FStkSetting Setting)
		{
			return Setting.Name == SoundToolKit::Utils::ShortName(StkParameter.name());
		});

		FString CurrentValue;
		if (SerializedParameter)
		{
			CurrentValue = SerializedParameter->CurrentValue;
			if (CurrentValue != ANSI_TO_TCHAR(StkParameter.defaultValue().c_str()))
			{
				StkParameter.setValue(TCHAR_TO_ANSI(*CurrentValue));
			}
		}
		else
		{
			CurrentValue = ANSI_TO_TCHAR(currentValue.c_str());
		}

		FString Name = SoundToolKit::Utils::ShortName(StkParameter.name());
		FString FullName(StkParameter.name().c_str());
		FString Category = FullName.Left(FullName.Len() - Name.Len() - 1);
		
		Category[0] = toupper(Category[0]);
		int32 DotIndex;
		while (Category.FindChar(TCHAR('.'), DotIndex))
		{
			Category[DotIndex + 1] = toupper(Category[DotIndex + 1]);
			Category[DotIndex] = TCHAR(' ');
		}

		NewSettings.Add(
			{ &StkParameter,
			Category,
			Name,
			ConvertType(StkParameter.type()),
			ANSI_TO_TCHAR(StkParameter.allowedValues().c_str()),
			ANSI_TO_TCHAR(StkParameter.description().c_str()),
			ANSI_TO_TCHAR(StkParameter.defaultValue().c_str()),
			CurrentValue });
	});

	StkGameModulePtr->Finish();
	Settings = MoveTemp(NewSettings);
}
