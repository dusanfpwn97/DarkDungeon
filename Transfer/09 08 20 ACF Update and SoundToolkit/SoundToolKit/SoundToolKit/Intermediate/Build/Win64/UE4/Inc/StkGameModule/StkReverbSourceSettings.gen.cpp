// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "StkGameModule/Public/StkReverbSourceSettings.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeStkReverbSourceSettings() {}
// Cross Module References
	STKGAMEMODULE_API UClass* Z_Construct_UClass_UStkReverbSourceSettings_NoRegister();
	STKGAMEMODULE_API UClass* Z_Construct_UClass_UStkReverbSourceSettings();
	AUDIOEXTENSIONS_API UClass* Z_Construct_UClass_UReverbPluginSourceSettingsBase();
	UPackage* Z_Construct_UPackage__Script_StkGameModule();
// End Cross Module References
	void UStkReverbSourceSettings::StaticRegisterNativesUStkReverbSourceSettings()
	{
	}
	UClass* Z_Construct_UClass_UStkReverbSourceSettings_NoRegister()
	{
		return UStkReverbSourceSettings::StaticClass();
	}
	struct Z_Construct_UClass_UStkReverbSourceSettings_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bReverbEnabled_MetaData[];
#endif
		static void NewProp_bReverbEnabled_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bReverbEnabled;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UStkReverbSourceSettings_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UReverbPluginSourceSettingsBase,
		(UObject* (*)())Z_Construct_UPackage__Script_StkGameModule,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UStkReverbSourceSettings_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "StkReverbSourceSettings.h" },
		{ "ModuleRelativePath", "Public/StkReverbSourceSettings.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UStkReverbSourceSettings_Statics::NewProp_bReverbEnabled_MetaData[] = {
		{ "Category", "Reverb Effect" },
		{ "Comment", "/// Whether or not the source should be reverb input.\n" },
		{ "ModuleRelativePath", "Public/StkReverbSourceSettings.h" },
		{ "ToolTip", "Whether or not the source should be reverb input." },
	};
#endif
	void Z_Construct_UClass_UStkReverbSourceSettings_Statics::NewProp_bReverbEnabled_SetBit(void* Obj)
	{
		((UStkReverbSourceSettings*)Obj)->bReverbEnabled = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UStkReverbSourceSettings_Statics::NewProp_bReverbEnabled = { "bReverbEnabled", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UStkReverbSourceSettings), &Z_Construct_UClass_UStkReverbSourceSettings_Statics::NewProp_bReverbEnabled_SetBit, METADATA_PARAMS(Z_Construct_UClass_UStkReverbSourceSettings_Statics::NewProp_bReverbEnabled_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UStkReverbSourceSettings_Statics::NewProp_bReverbEnabled_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UStkReverbSourceSettings_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UStkReverbSourceSettings_Statics::NewProp_bReverbEnabled,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UStkReverbSourceSettings_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UStkReverbSourceSettings>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UStkReverbSourceSettings_Statics::ClassParams = {
		&UStkReverbSourceSettings::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UStkReverbSourceSettings_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UStkReverbSourceSettings_Statics::PropPointers),
		0,
		0x001010A0u,
		METADATA_PARAMS(Z_Construct_UClass_UStkReverbSourceSettings_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UStkReverbSourceSettings_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UStkReverbSourceSettings()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UStkReverbSourceSettings_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UStkReverbSourceSettings, 2696883885);
	template<> STKGAMEMODULE_API UClass* StaticClass<UStkReverbSourceSettings>()
	{
		return UStkReverbSourceSettings::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UStkReverbSourceSettings(Z_Construct_UClass_UStkReverbSourceSettings, &UStkReverbSourceSettings::StaticClass, TEXT("/Script/StkGameModule"), TEXT("UStkReverbSourceSettings"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UStkReverbSourceSettings);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
