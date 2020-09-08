// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "StkGameModule/Private/StkSettings.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeStkSettings() {}
// Cross Module References
	STKGAMEMODULE_API UEnum* Z_Construct_UEnum_StkGameModule_EStkSettingType();
	UPackage* Z_Construct_UPackage__Script_StkGameModule();
	STKGAMEMODULE_API UScriptStruct* Z_Construct_UScriptStruct_FStkSetting();
	STKGAMEMODULE_API UClass* Z_Construct_UClass_UStkSettings_NoRegister();
	STKGAMEMODULE_API UClass* Z_Construct_UClass_UStkSettings();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
// End Cross Module References
	static UEnum* EStkSettingType_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_StkGameModule_EStkSettingType, Z_Construct_UPackage__Script_StkGameModule(), TEXT("EStkSettingType"));
		}
		return Singleton;
	}
	template<> STKGAMEMODULE_API UEnum* StaticEnum<EStkSettingType>()
	{
		return EStkSettingType_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_EStkSettingType(EStkSettingType_StaticEnum, TEXT("/Script/StkGameModule"), TEXT("EStkSettingType"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_StkGameModule_EStkSettingType_Hash() { return 2828054820U; }
	UEnum* Z_Construct_UEnum_StkGameModule_EStkSettingType()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_StkGameModule();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("EStkSettingType"), 0, Get_Z_Construct_UEnum_StkGameModule_EStkSettingType_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "EStkSettingType::StkSettingType_Boolean", (int64)EStkSettingType::StkSettingType_Boolean },
				{ "EStkSettingType::StkSettingType_Enumeration", (int64)EStkSettingType::StkSettingType_Enumeration },
				{ "EStkSettingType::StkSettingType_Integer", (int64)EStkSettingType::StkSettingType_Integer },
				{ "EStkSettingType::StkSettingType_Float", (int64)EStkSettingType::StkSettingType_Float },
				{ "EStkSettingType::StkSettingType_ListOfIntegers", (int64)EStkSettingType::StkSettingType_ListOfIntegers },
				{ "EStkSettingType::StkSettingType_ListOfFloats", (int64)EStkSettingType::StkSettingType_ListOfFloats },
			};
#if WITH_METADATA
			const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "ModuleRelativePath", "Private/StkSettings.h" },
				{ "StkSettingType_Boolean.DisplayName", "Boolean" },
				{ "StkSettingType_Boolean.Name", "EStkSettingType::StkSettingType_Boolean" },
				{ "StkSettingType_Enumeration.DisplayName", "Enumeration" },
				{ "StkSettingType_Enumeration.Name", "EStkSettingType::StkSettingType_Enumeration" },
				{ "StkSettingType_Float.DisplayName", "Float" },
				{ "StkSettingType_Float.Name", "EStkSettingType::StkSettingType_Float" },
				{ "StkSettingType_Integer.DisplayName", "Integer" },
				{ "StkSettingType_Integer.Name", "EStkSettingType::StkSettingType_Integer" },
				{ "StkSettingType_ListOfFloats.DisplayName", "List Of Floats" },
				{ "StkSettingType_ListOfFloats.Name", "EStkSettingType::StkSettingType_ListOfFloats" },
				{ "StkSettingType_ListOfIntegers.DisplayName", "List Of Integers" },
				{ "StkSettingType_ListOfIntegers.Name", "EStkSettingType::StkSettingType_ListOfIntegers" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_StkGameModule,
				nullptr,
				"EStkSettingType",
				"EStkSettingType",
				Enumerators,
				UE_ARRAY_COUNT(Enumerators),
				RF_Public|RF_Transient|RF_MarkAsNative,
				UE4CodeGen_Private::EDynamicType::NotDynamic,
				(uint8)UEnum::ECppForm::EnumClass,
				METADATA_PARAMS(Enum_MetaDataParams, UE_ARRAY_COUNT(Enum_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams);
		}
		return ReturnEnum;
	}
class UScriptStruct* FStkSetting::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern STKGAMEMODULE_API uint32 Get_Z_Construct_UScriptStruct_FStkSetting_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FStkSetting, Z_Construct_UPackage__Script_StkGameModule(), TEXT("StkSetting"), sizeof(FStkSetting), Get_Z_Construct_UScriptStruct_FStkSetting_Hash());
	}
	return Singleton;
}
template<> STKGAMEMODULE_API UScriptStruct* StaticStruct<FStkSetting>()
{
	return FStkSetting::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FStkSetting(FStkSetting::StaticStruct, TEXT("/Script/StkGameModule"), TEXT("StkSetting"), false, nullptr, nullptr);
static struct FScriptStruct_StkGameModule_StaticRegisterNativesFStkSetting
{
	FScriptStruct_StkGameModule_StaticRegisterNativesFStkSetting()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("StkSetting")),new UScriptStruct::TCppStructOps<FStkSetting>);
	}
} ScriptStruct_StkGameModule_StaticRegisterNativesFStkSetting;
	struct Z_Construct_UScriptStruct_FStkSetting_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CurrentValue_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_CurrentValue;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Name_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Name;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Category_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Category;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FStkSetting_Statics::Struct_MetaDataParams[] = {
		{ "Comment", "///\x09Holds values of an stk::Parameter object.\n" },
		{ "ModuleRelativePath", "Private/StkSettings.h" },
		{ "ToolTip", "Holds values of an stk::Parameter object." },
	};
#endif
	void* Z_Construct_UScriptStruct_FStkSetting_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FStkSetting>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FStkSetting_Statics::NewProp_CurrentValue_MetaData[] = {
		{ "ModuleRelativePath", "Private/StkSettings.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FStkSetting_Statics::NewProp_CurrentValue = { "CurrentValue", nullptr, (EPropertyFlags)0x0010000000004000, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FStkSetting, CurrentValue), METADATA_PARAMS(Z_Construct_UScriptStruct_FStkSetting_Statics::NewProp_CurrentValue_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FStkSetting_Statics::NewProp_CurrentValue_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FStkSetting_Statics::NewProp_Name_MetaData[] = {
		{ "ModuleRelativePath", "Private/StkSettings.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FStkSetting_Statics::NewProp_Name = { "Name", nullptr, (EPropertyFlags)0x0010000000004000, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FStkSetting, Name), METADATA_PARAMS(Z_Construct_UScriptStruct_FStkSetting_Statics::NewProp_Name_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FStkSetting_Statics::NewProp_Name_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FStkSetting_Statics::NewProp_Category_MetaData[] = {
		{ "ModuleRelativePath", "Private/StkSettings.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FStkSetting_Statics::NewProp_Category = { "Category", nullptr, (EPropertyFlags)0x0010000000004000, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FStkSetting, Category), METADATA_PARAMS(Z_Construct_UScriptStruct_FStkSetting_Statics::NewProp_Category_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FStkSetting_Statics::NewProp_Category_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FStkSetting_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FStkSetting_Statics::NewProp_CurrentValue,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FStkSetting_Statics::NewProp_Name,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FStkSetting_Statics::NewProp_Category,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FStkSetting_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_StkGameModule,
		nullptr,
		&NewStructOps,
		"StkSetting",
		sizeof(FStkSetting),
		alignof(FStkSetting),
		Z_Construct_UScriptStruct_FStkSetting_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FStkSetting_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000201),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FStkSetting_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FStkSetting_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FStkSetting()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FStkSetting_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_StkGameModule();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("StkSetting"), sizeof(FStkSetting), Get_Z_Construct_UScriptStruct_FStkSetting_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FStkSetting_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FStkSetting_Hash() { return 1050528272U; }
	void UStkSettings::StaticRegisterNativesUStkSettings()
	{
	}
	UClass* Z_Construct_UClass_UStkSettings_NoRegister()
	{
		return UStkSettings::StaticClass();
	}
	struct Z_Construct_UClass_UStkSettings_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Settings_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_Settings;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Settings_Inner;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UStkSettings_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_StkGameModule,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UStkSettings_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/// Responsible for storing FStkParameters and managing stk::Settings.\n" },
		{ "IncludePath", "StkSettings.h" },
		{ "ModuleRelativePath", "Private/StkSettings.h" },
		{ "ToolTip", "Responsible for storing FStkParameters and managing stk::Settings." },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UStkSettings_Statics::NewProp_Settings_MetaData[] = {
		{ "Comment", "// End of UObject interface\n" },
		{ "ModuleRelativePath", "Private/StkSettings.h" },
		{ "ToolTip", "End of UObject interface" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UStkSettings_Statics::NewProp_Settings = { "Settings", nullptr, (EPropertyFlags)0x0010000000004000, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UStkSettings, Settings), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_UStkSettings_Statics::NewProp_Settings_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UStkSettings_Statics::NewProp_Settings_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_UStkSettings_Statics::NewProp_Settings_Inner = { "Settings", nullptr, (EPropertyFlags)0x0000000000004000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FStkSetting, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UStkSettings_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UStkSettings_Statics::NewProp_Settings,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UStkSettings_Statics::NewProp_Settings_Inner,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UStkSettings_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UStkSettings>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UStkSettings_Statics::ClassParams = {
		&UStkSettings::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UStkSettings_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UStkSettings_Statics::PropPointers),
		0,
		0x001000A4u,
		METADATA_PARAMS(Z_Construct_UClass_UStkSettings_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UStkSettings_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UStkSettings()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UStkSettings_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UStkSettings, 426030615);
	template<> STKGAMEMODULE_API UClass* StaticClass<UStkSettings>()
	{
		return UStkSettings::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UStkSettings(Z_Construct_UClass_UStkSettings, &UStkSettings::StaticClass, TEXT("/Script/StkGameModule"), TEXT("UStkSettings"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UStkSettings);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
