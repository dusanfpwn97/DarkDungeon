// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "StkGameModule/Public/StkSpatializationSourceSettings.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeStkSpatializationSourceSettings() {}
// Cross Module References
	STKGAMEMODULE_API UClass* Z_Construct_UClass_UStkSpatializationSourceSettings_NoRegister();
	STKGAMEMODULE_API UClass* Z_Construct_UClass_UStkSpatializationSourceSettings();
	AUDIOEXTENSIONS_API UClass* Z_Construct_UClass_USpatializationPluginSourceSettingsBase();
	UPackage* Z_Construct_UPackage__Script_StkGameModule();
	ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FRuntimeFloatCurve();
	STKGAMEMODULE_API UEnum* Z_Construct_UEnum_StkGameModule_EStkAttenuationFunction();
// End Cross Module References
	void UStkSpatializationSourceSettings::StaticRegisterNativesUStkSpatializationSourceSettings()
	{
	}
	UClass* Z_Construct_UClass_UStkSpatializationSourceSettings_NoRegister()
	{
		return UStkSpatializationSourceSettings::StaticClass();
	}
	struct Z_Construct_UClass_UStkSpatializationSourceSettings_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bUseHrtfSpatialization_MetaData[];
#endif
		static void NewProp_bUseHrtfSpatialization_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bUseHrtfSpatialization;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_FallofDistance_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_FallofDistance;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_InnerRadius_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_InnerRadius;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CustomAttenuation_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_CustomAttenuation;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Attenuation_MetaData[];
#endif
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_Attenuation;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_Attenuation_Underlying;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UStkSpatializationSourceSettings_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_USpatializationPluginSourceSettingsBase,
		(UObject* (*)())Z_Construct_UPackage__Script_StkGameModule,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UStkSpatializationSourceSettings_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "StkSpatializationSourceSettings.h" },
		{ "ModuleRelativePath", "Public/StkSpatializationSourceSettings.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UStkSpatializationSourceSettings_Statics::NewProp_bUseHrtfSpatialization_MetaData[] = {
		{ "Category", "Spatial Effects" },
		{ "Comment", "/// Whether or not HRTF functions should be used.\n" },
		{ "ModuleRelativePath", "Public/StkSpatializationSourceSettings.h" },
		{ "ToolTip", "Whether or not HRTF functions should be used." },
	};
#endif
	void Z_Construct_UClass_UStkSpatializationSourceSettings_Statics::NewProp_bUseHrtfSpatialization_SetBit(void* Obj)
	{
		((UStkSpatializationSourceSettings*)Obj)->bUseHrtfSpatialization = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UStkSpatializationSourceSettings_Statics::NewProp_bUseHrtfSpatialization = { "bUseHrtfSpatialization", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UStkSpatializationSourceSettings), &Z_Construct_UClass_UStkSpatializationSourceSettings_Statics::NewProp_bUseHrtfSpatialization_SetBit, METADATA_PARAMS(Z_Construct_UClass_UStkSpatializationSourceSettings_Statics::NewProp_bUseHrtfSpatialization_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UStkSpatializationSourceSettings_Statics::NewProp_bUseHrtfSpatialization_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UStkSpatializationSourceSettings_Statics::NewProp_FallofDistance_MetaData[] = {
		{ "Category", "Spatial Effects" },
		{ "ClampMin", "0.0" },
		{ "Comment", "/// The distance over which sound attenuation occurs.\n" },
		{ "ModuleRelativePath", "Public/StkSpatializationSourceSettings.h" },
		{ "ToolTip", "The distance over which sound attenuation occurs." },
		{ "UIMin", "0.0" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UStkSpatializationSourceSettings_Statics::NewProp_FallofDistance = { "FallofDistance", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UStkSpatializationSourceSettings, FallofDistance), METADATA_PARAMS(Z_Construct_UClass_UStkSpatializationSourceSettings_Statics::NewProp_FallofDistance_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UStkSpatializationSourceSettings_Statics::NewProp_FallofDistance_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UStkSpatializationSourceSettings_Statics::NewProp_InnerRadius_MetaData[] = {
		{ "Category", "Spatial Effects" },
		{ "ClampMin", "0.0" },
		{ "Comment", "/// The radius of the sound source at which sound is not attenuated.\n" },
		{ "ModuleRelativePath", "Public/StkSpatializationSourceSettings.h" },
		{ "ToolTip", "The radius of the sound source at which sound is not attenuated." },
		{ "UIMin", "0.0" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UStkSpatializationSourceSettings_Statics::NewProp_InnerRadius = { "InnerRadius", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UStkSpatializationSourceSettings, InnerRadius), METADATA_PARAMS(Z_Construct_UClass_UStkSpatializationSourceSettings_Statics::NewProp_InnerRadius_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UStkSpatializationSourceSettings_Statics::NewProp_InnerRadius_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UStkSpatializationSourceSettings_Statics::NewProp_CustomAttenuation_MetaData[] = {
		{ "Category", "Spatial Effects" },
		{ "ClampFloatTangent", "1.0" },
		{ "Comment", "/// The custom attenuation curve. Only range of (0,1) in both axes.\n" },
		{ "ModuleRelativePath", "Public/StkSpatializationSourceSettings.h" },
		{ "ToolTip", "The custom attenuation curve. Only range of (0,1) in both axes." },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_UStkSpatializationSourceSettings_Statics::NewProp_CustomAttenuation = { "CustomAttenuation", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UStkSpatializationSourceSettings, CustomAttenuation), Z_Construct_UScriptStruct_FRuntimeFloatCurve, METADATA_PARAMS(Z_Construct_UClass_UStkSpatializationSourceSettings_Statics::NewProp_CustomAttenuation_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UStkSpatializationSourceSettings_Statics::NewProp_CustomAttenuation_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UStkSpatializationSourceSettings_Statics::NewProp_Attenuation_MetaData[] = {
		{ "Category", "Spatial Effects" },
		{ "Comment", "/// The attenuation with distance function to use.\n" },
		{ "ModuleRelativePath", "Public/StkSpatializationSourceSettings.h" },
		{ "ToolTip", "The attenuation with distance function to use." },
	};
#endif
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UStkSpatializationSourceSettings_Statics::NewProp_Attenuation = { "Attenuation", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UStkSpatializationSourceSettings, Attenuation), Z_Construct_UEnum_StkGameModule_EStkAttenuationFunction, METADATA_PARAMS(Z_Construct_UClass_UStkSpatializationSourceSettings_Statics::NewProp_Attenuation_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UStkSpatializationSourceSettings_Statics::NewProp_Attenuation_MetaData)) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UClass_UStkSpatializationSourceSettings_Statics::NewProp_Attenuation_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UStkSpatializationSourceSettings_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UStkSpatializationSourceSettings_Statics::NewProp_bUseHrtfSpatialization,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UStkSpatializationSourceSettings_Statics::NewProp_FallofDistance,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UStkSpatializationSourceSettings_Statics::NewProp_InnerRadius,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UStkSpatializationSourceSettings_Statics::NewProp_CustomAttenuation,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UStkSpatializationSourceSettings_Statics::NewProp_Attenuation,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UStkSpatializationSourceSettings_Statics::NewProp_Attenuation_Underlying,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UStkSpatializationSourceSettings_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UStkSpatializationSourceSettings>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UStkSpatializationSourceSettings_Statics::ClassParams = {
		&UStkSpatializationSourceSettings::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UStkSpatializationSourceSettings_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UStkSpatializationSourceSettings_Statics::PropPointers),
		0,
		0x001010A0u,
		METADATA_PARAMS(Z_Construct_UClass_UStkSpatializationSourceSettings_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UStkSpatializationSourceSettings_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UStkSpatializationSourceSettings()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UStkSpatializationSourceSettings_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UStkSpatializationSourceSettings, 409497941);
	template<> STKGAMEMODULE_API UClass* StaticClass<UStkSpatializationSourceSettings>()
	{
		return UStkSpatializationSourceSettings::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UStkSpatializationSourceSettings(Z_Construct_UClass_UStkSpatializationSourceSettings, &UStkSpatializationSourceSettings::StaticClass, TEXT("/Script/StkGameModule"), TEXT("UStkSpatializationSourceSettings"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UStkSpatializationSourceSettings);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
