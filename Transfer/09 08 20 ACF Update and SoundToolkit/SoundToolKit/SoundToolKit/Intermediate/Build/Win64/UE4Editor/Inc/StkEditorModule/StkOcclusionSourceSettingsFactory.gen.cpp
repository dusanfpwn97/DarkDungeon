// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "StkEditorModule/Private/StkOcclusionSourceSettingsFactory.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeStkOcclusionSourceSettingsFactory() {}
// Cross Module References
	STKEDITORMODULE_API UClass* Z_Construct_UClass_UStkOcclusionSourceSettingsFactory_NoRegister();
	STKEDITORMODULE_API UClass* Z_Construct_UClass_UStkOcclusionSourceSettingsFactory();
	UNREALED_API UClass* Z_Construct_UClass_UFactory();
	UPackage* Z_Construct_UPackage__Script_StkEditorModule();
// End Cross Module References
	void UStkOcclusionSourceSettingsFactory::StaticRegisterNativesUStkOcclusionSourceSettingsFactory()
	{
	}
	UClass* Z_Construct_UClass_UStkOcclusionSourceSettingsFactory_NoRegister()
	{
		return UStkOcclusionSourceSettingsFactory::StaticClass();
	}
	struct Z_Construct_UClass_UStkOcclusionSourceSettingsFactory_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UStkOcclusionSourceSettingsFactory_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UFactory,
		(UObject* (*)())Z_Construct_UPackage__Script_StkEditorModule,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UStkOcclusionSourceSettingsFactory_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "StkOcclusionSourceSettingsFactory.h" },
		{ "ModuleRelativePath", "Private/StkOcclusionSourceSettingsFactory.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UStkOcclusionSourceSettingsFactory_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UStkOcclusionSourceSettingsFactory>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UStkOcclusionSourceSettingsFactory_Statics::ClassParams = {
		&UStkOcclusionSourceSettingsFactory::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x000000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UStkOcclusionSourceSettingsFactory_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UStkOcclusionSourceSettingsFactory_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UStkOcclusionSourceSettingsFactory()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UStkOcclusionSourceSettingsFactory_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UStkOcclusionSourceSettingsFactory, 171829861);
	template<> STKEDITORMODULE_API UClass* StaticClass<UStkOcclusionSourceSettingsFactory>()
	{
		return UStkOcclusionSourceSettingsFactory::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UStkOcclusionSourceSettingsFactory(Z_Construct_UClass_UStkOcclusionSourceSettingsFactory, &UStkOcclusionSourceSettingsFactory::StaticClass, TEXT("/Script/StkEditorModule"), TEXT("UStkOcclusionSourceSettingsFactory"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UStkOcclusionSourceSettingsFactory);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
