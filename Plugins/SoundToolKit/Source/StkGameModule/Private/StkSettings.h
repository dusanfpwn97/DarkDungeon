//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#pragma once

#include "StkSettings.generated.h"

namespace stk
{
	class ISetting;
}

namespace SoundToolKit
{
	class FStkGameModule;
}

UENUM()
enum class EStkSettingType : uint8
{
	StkSettingType_Boolean UMETA(DisplayName = "Boolean"),
	StkSettingType_Enumeration UMETA(DisplayName = "Enumeration"),
	StkSettingType_Integer UMETA(DisplayName = "Integer"),
	StkSettingType_Float UMETA(DisplayName = "Float"),
	StkSettingType_ListOfIntegers UMETA(DisplayName = "List Of Integers"),
	StkSettingType_ListOfFloats UMETA(DisplayName = "List Of Floats")
};

///	Holds values of an stk::Parameter object.
USTRUCT()
struct STKGAMEMODULE_API FStkSetting
{
	GENERATED_BODY()

	FStkSetting();
	FStkSetting(
		stk::ISetting* Parameter,
		const FString& CategoryIn,
		const FString& NameIn,
		EStkSettingType TypeIn,
		const FString& AllowedValuesIn,
		const FString& DescriptionIn,
		const FString& DefaultValueIn,
		const FString& CurrentValueIn);

	/// <summary>
	/// Indicates whether Update() should be called.
	/// </summary>
	bool IsPendingUpdate();

	/// <summary>
	/// Sets the parameter value within STK engine.
	/// </summary>
	void Update();

	UPROPERTY(Config)
	FString Category;

	UPROPERTY(Config)
	FString Name;

	EStkSettingType Type;

	FString AllowedValues;

	FString Description;

	FString DefaultValue;

	UPROPERTY(Config)
	FString CurrentValue;

private:
	FString OldValue;

	stk::ISetting* StkParameter;
};

/// Responsible for storing FStkParameters and managing stk::Settings.
UCLASS(config=Game)
class STKGAMEMODULE_API UStkSettings : public UObject
{
	GENERATED_BODY()

public:
	UStkSettings();

	TArray<FStkSetting>& GetSettings();

	// UObject interface
	virtual void PostInitProperties() override;
	// End of UObject interface

	UPROPERTY(Config)
	TArray<FStkSetting> Settings;

private:
	/// <summary>
	/// Called on initialization, loads serialized FStkParameters and checks for new stk::Parameters.
	/// </summary>
	void ValidateSettings();

	SoundToolKit::FStkGameModule* StkGameModulePtr;
};
