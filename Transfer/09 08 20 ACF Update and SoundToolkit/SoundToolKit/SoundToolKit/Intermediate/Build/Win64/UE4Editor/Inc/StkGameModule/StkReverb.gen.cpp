// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "StkGameModule/Private/StkReverb.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeStkReverb() {}
// Cross Module References
	STKGAMEMODULE_API UScriptStruct* Z_Construct_UScriptStruct_FStkSubmixEffectReverbPluginSettings();
	UPackage* Z_Construct_UPackage__Script_StkGameModule();
	STKGAMEMODULE_API UClass* Z_Construct_UClass_UStkSubmixEffectReverbPluginPreset_NoRegister();
	STKGAMEMODULE_API UClass* Z_Construct_UClass_UStkSubmixEffectReverbPluginPreset();
	ENGINE_API UClass* Z_Construct_UClass_USoundEffectSubmixPreset();
// End Cross Module References
class UScriptStruct* FStkSubmixEffectReverbPluginSettings::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern STKGAMEMODULE_API uint32 Get_Z_Construct_UScriptStruct_FStkSubmixEffectReverbPluginSettings_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FStkSubmixEffectReverbPluginSettings, Z_Construct_UPackage__Script_StkGameModule(), TEXT("StkSubmixEffectReverbPluginSettings"), sizeof(FStkSubmixEffectReverbPluginSettings), Get_Z_Construct_UScriptStruct_FStkSubmixEffectReverbPluginSettings_Hash());
	}
	return Singleton;
}
template<> STKGAMEMODULE_API UScriptStruct* StaticStruct<FStkSubmixEffectReverbPluginSettings>()
{
	return FStkSubmixEffectReverbPluginSettings::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FStkSubmixEffectReverbPluginSettings(FStkSubmixEffectReverbPluginSettings::StaticStruct, TEXT("/Script/StkGameModule"), TEXT("StkSubmixEffectReverbPluginSettings"), false, nullptr, nullptr);
static struct FScriptStruct_StkGameModule_StaticRegisterNativesFStkSubmixEffectReverbPluginSettings
{
	FScriptStruct_StkGameModule_StaticRegisterNativesFStkSubmixEffectReverbPluginSettings()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("StkSubmixEffectReverbPluginSettings")),new UScriptStruct::TCppStructOps<FStkSubmixEffectReverbPluginSettings>);
	}
} ScriptStruct_StkGameModule_StaticRegisterNativesFStkSubmixEffectReverbPluginSettings;
	struct Z_Construct_UScriptStruct_FStkSubmixEffectReverbPluginSettings_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FStkSubmixEffectReverbPluginSettings_Statics::Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "Private/StkReverb.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FStkSubmixEffectReverbPluginSettings_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FStkSubmixEffectReverbPluginSettings>();
	}
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FStkSubmixEffectReverbPluginSettings_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_StkGameModule,
		nullptr,
		&NewStructOps,
		"StkSubmixEffectReverbPluginSettings",
		sizeof(FStkSubmixEffectReverbPluginSettings),
		alignof(FStkSubmixEffectReverbPluginSettings),
		nullptr,
		0,
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FStkSubmixEffectReverbPluginSettings_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FStkSubmixEffectReverbPluginSettings_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FStkSubmixEffectReverbPluginSettings()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FStkSubmixEffectReverbPluginSettings_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_StkGameModule();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("StkSubmixEffectReverbPluginSettings"), sizeof(FStkSubmixEffectReverbPluginSettings), Get_Z_Construct_UScriptStruct_FStkSubmixEffectReverbPluginSettings_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FStkSubmixEffectReverbPluginSettings_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FStkSubmixEffectReverbPluginSettings_Hash() { return 3905715103U; }
	void UStkSubmixEffectReverbPluginPreset::StaticRegisterNativesUStkSubmixEffectReverbPluginPreset()
	{
	}
	UClass* Z_Construct_UClass_UStkSubmixEffectReverbPluginPreset_NoRegister()
	{
		return UStkSubmixEffectReverbPluginPreset::StaticClass();
	}
	struct Z_Construct_UClass_UStkSubmixEffectReverbPluginPreset_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Settings_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Settings;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UStkSubmixEffectReverbPluginPreset_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_USoundEffectSubmixPreset,
		(UObject* (*)())Z_Construct_UPackage__Script_StkGameModule,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UStkSubmixEffectReverbPluginPreset_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Object" },
		{ "IncludePath", "StkReverb.h" },
		{ "ModuleRelativePath", "Private/StkReverb.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UStkSubmixEffectReverbPluginPreset_Statics::NewProp_Settings_MetaData[] = {
		{ "Category", "SubmixEffectPreset" },
		{ "ModuleRelativePath", "Private/StkReverb.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_UStkSubmixEffectReverbPluginPreset_Statics::NewProp_Settings = { "Settings", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UStkSubmixEffectReverbPluginPreset, Settings), Z_Construct_UScriptStruct_FStkSubmixEffectReverbPluginSettings, METADATA_PARAMS(Z_Construct_UClass_UStkSubmixEffectReverbPluginPreset_Statics::NewProp_Settings_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UStkSubmixEffectReverbPluginPreset_Statics::NewProp_Settings_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UStkSubmixEffectReverbPluginPreset_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UStkSubmixEffectReverbPluginPreset_Statics::NewProp_Settings,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UStkSubmixEffectReverbPluginPreset_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UStkSubmixEffectReverbPluginPreset>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UStkSubmixEffectReverbPluginPreset_Statics::ClassParams = {
		&UStkSubmixEffectReverbPluginPreset::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UStkSubmixEffectReverbPluginPreset_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UStkSubmixEffectReverbPluginPreset_Statics::PropPointers),
		0,
		0x000010A0u,
		METADATA_PARAMS(Z_Construct_UClass_UStkSubmixEffectReverbPluginPreset_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UStkSubmixEffectReverbPluginPreset_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UStkSubmixEffectReverbPluginPreset()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UStkSubmixEffectReverbPluginPreset_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UStkSubmixEffectReverbPluginPreset, 1742890989);
	template<> STKGAMEMODULE_API UClass* StaticClass<UStkSubmixEffectReverbPluginPreset>()
	{
		return UStkSubmixEffectReverbPluginPreset::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UStkSubmixEffectReverbPluginPreset(Z_Construct_UClass_UStkSubmixEffectReverbPluginPreset, &UStkSubmixEffectReverbPluginPreset::StaticClass, TEXT("/Script/StkGameModule"), TEXT("UStkSubmixEffectReverbPluginPreset"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UStkSubmixEffectReverbPluginPreset);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
