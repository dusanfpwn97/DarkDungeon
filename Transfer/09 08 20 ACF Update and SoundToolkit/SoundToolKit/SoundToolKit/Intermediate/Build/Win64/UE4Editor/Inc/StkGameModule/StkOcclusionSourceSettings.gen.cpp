// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "StkGameModule/Public/StkOcclusionSourceSettings.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeStkOcclusionSourceSettings() {}
// Cross Module References
	STKGAMEMODULE_API UClass* Z_Construct_UClass_UStkOcclusionSourceSettings_NoRegister();
	STKGAMEMODULE_API UClass* Z_Construct_UClass_UStkOcclusionSourceSettings();
	AUDIOEXTENSIONS_API UClass* Z_Construct_UClass_UOcclusionPluginSourceSettingsBase();
	UPackage* Z_Construct_UPackage__Script_StkGameModule();
// End Cross Module References
	void UStkOcclusionSourceSettings::StaticRegisterNativesUStkOcclusionSourceSettings()
	{
	}
	UClass* Z_Construct_UClass_UStkOcclusionSourceSettings_NoRegister()
	{
		return UStkOcclusionSourceSettings::StaticClass();
	}
	struct Z_Construct_UClass_UStkOcclusionSourceSettings_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bDiffractionEnabled_MetaData[];
#endif
		static void NewProp_bDiffractionEnabled_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bDiffractionEnabled;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bTransmissionEnabled_MetaData[];
#endif
		static void NewProp_bTransmissionEnabled_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bTransmissionEnabled;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bReflectionEnabled_MetaData[];
#endif
		static void NewProp_bReflectionEnabled_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bReflectionEnabled;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UStkOcclusionSourceSettings_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UOcclusionPluginSourceSettingsBase,
		(UObject* (*)())Z_Construct_UPackage__Script_StkGameModule,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UStkOcclusionSourceSettings_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "StkOcclusionSourceSettings.h" },
		{ "ModuleRelativePath", "Public/StkOcclusionSourceSettings.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UStkOcclusionSourceSettings_Statics::NewProp_bDiffractionEnabled_MetaData[] = {
		{ "Category", "Occlusion Effects" },
		{ "Comment", "/// Whether or not the sound from source can be diffrated at the edges.\n" },
		{ "ModuleRelativePath", "Public/StkOcclusionSourceSettings.h" },
		{ "ToolTip", "Whether or not the sound from source can be diffrated at the edges." },
	};
#endif
	void Z_Construct_UClass_UStkOcclusionSourceSettings_Statics::NewProp_bDiffractionEnabled_SetBit(void* Obj)
	{
		((UStkOcclusionSourceSettings*)Obj)->bDiffractionEnabled = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UStkOcclusionSourceSettings_Statics::NewProp_bDiffractionEnabled = { "bDiffractionEnabled", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UStkOcclusionSourceSettings), &Z_Construct_UClass_UStkOcclusionSourceSettings_Statics::NewProp_bDiffractionEnabled_SetBit, METADATA_PARAMS(Z_Construct_UClass_UStkOcclusionSourceSettings_Statics::NewProp_bDiffractionEnabled_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UStkOcclusionSourceSettings_Statics::NewProp_bDiffractionEnabled_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UStkOcclusionSourceSettings_Statics::NewProp_bTransmissionEnabled_MetaData[] = {
		{ "Category", "Occlusion Effects" },
		{ "Comment", "/// Whether or not the sound from source can be transmitted through the acoustic obstacles.\n" },
		{ "ModuleRelativePath", "Public/StkOcclusionSourceSettings.h" },
		{ "ToolTip", "Whether or not the sound from source can be transmitted through the acoustic obstacles." },
	};
#endif
	void Z_Construct_UClass_UStkOcclusionSourceSettings_Statics::NewProp_bTransmissionEnabled_SetBit(void* Obj)
	{
		((UStkOcclusionSourceSettings*)Obj)->bTransmissionEnabled = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UStkOcclusionSourceSettings_Statics::NewProp_bTransmissionEnabled = { "bTransmissionEnabled", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UStkOcclusionSourceSettings), &Z_Construct_UClass_UStkOcclusionSourceSettings_Statics::NewProp_bTransmissionEnabled_SetBit, METADATA_PARAMS(Z_Construct_UClass_UStkOcclusionSourceSettings_Statics::NewProp_bTransmissionEnabled_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UStkOcclusionSourceSettings_Statics::NewProp_bTransmissionEnabled_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UStkOcclusionSourceSettings_Statics::NewProp_bReflectionEnabled_MetaData[] = {
		{ "Category", "Occlusion Effects" },
		{ "Comment", "/// Whether or not the sound from source can be reflected from acoustic obstacles.\n" },
		{ "ModuleRelativePath", "Public/StkOcclusionSourceSettings.h" },
		{ "ToolTip", "Whether or not the sound from source can be reflected from acoustic obstacles." },
	};
#endif
	void Z_Construct_UClass_UStkOcclusionSourceSettings_Statics::NewProp_bReflectionEnabled_SetBit(void* Obj)
	{
		((UStkOcclusionSourceSettings*)Obj)->bReflectionEnabled = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UStkOcclusionSourceSettings_Statics::NewProp_bReflectionEnabled = { "bReflectionEnabled", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UStkOcclusionSourceSettings), &Z_Construct_UClass_UStkOcclusionSourceSettings_Statics::NewProp_bReflectionEnabled_SetBit, METADATA_PARAMS(Z_Construct_UClass_UStkOcclusionSourceSettings_Statics::NewProp_bReflectionEnabled_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UStkOcclusionSourceSettings_Statics::NewProp_bReflectionEnabled_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UStkOcclusionSourceSettings_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UStkOcclusionSourceSettings_Statics::NewProp_bDiffractionEnabled,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UStkOcclusionSourceSettings_Statics::NewProp_bTransmissionEnabled,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UStkOcclusionSourceSettings_Statics::NewProp_bReflectionEnabled,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UStkOcclusionSourceSettings_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UStkOcclusionSourceSettings>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UStkOcclusionSourceSettings_Statics::ClassParams = {
		&UStkOcclusionSourceSettings::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UStkOcclusionSourceSettings_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UStkOcclusionSourceSettings_Statics::PropPointers),
		0,
		0x001010A0u,
		METADATA_PARAMS(Z_Construct_UClass_UStkOcclusionSourceSettings_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UStkOcclusionSourceSettings_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UStkOcclusionSourceSettings()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UStkOcclusionSourceSettings_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UStkOcclusionSourceSettings, 367343660);
	template<> STKGAMEMODULE_API UClass* StaticClass<UStkOcclusionSourceSettings>()
	{
		return UStkOcclusionSourceSettings::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UStkOcclusionSourceSettings(Z_Construct_UClass_UStkOcclusionSourceSettings, &UStkOcclusionSourceSettings::StaticClass, TEXT("/Script/StkGameModule"), TEXT("UStkOcclusionSourceSettings"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UStkOcclusionSourceSettings);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
