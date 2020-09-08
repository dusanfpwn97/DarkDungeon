// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "StkEditorModule/Private/StkAcousticMaterialFactory.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeStkAcousticMaterialFactory() {}
// Cross Module References
	STKEDITORMODULE_API UClass* Z_Construct_UClass_UStkAcousticMaterialFactory_NoRegister();
	STKEDITORMODULE_API UClass* Z_Construct_UClass_UStkAcousticMaterialFactory();
	UNREALED_API UClass* Z_Construct_UClass_UFactory();
	UPackage* Z_Construct_UPackage__Script_StkEditorModule();
// End Cross Module References
	void UStkAcousticMaterialFactory::StaticRegisterNativesUStkAcousticMaterialFactory()
	{
	}
	UClass* Z_Construct_UClass_UStkAcousticMaterialFactory_NoRegister()
	{
		return UStkAcousticMaterialFactory::StaticClass();
	}
	struct Z_Construct_UClass_UStkAcousticMaterialFactory_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UStkAcousticMaterialFactory_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UFactory,
		(UObject* (*)())Z_Construct_UPackage__Script_StkEditorModule,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UStkAcousticMaterialFactory_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "StkAcousticMaterialFactory.h" },
		{ "ModuleRelativePath", "Private/StkAcousticMaterialFactory.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UStkAcousticMaterialFactory_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UStkAcousticMaterialFactory>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UStkAcousticMaterialFactory_Statics::ClassParams = {
		&UStkAcousticMaterialFactory::StaticClass,
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
		METADATA_PARAMS(Z_Construct_UClass_UStkAcousticMaterialFactory_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UStkAcousticMaterialFactory_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UStkAcousticMaterialFactory()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UStkAcousticMaterialFactory_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UStkAcousticMaterialFactory, 3474221779);
	template<> STKEDITORMODULE_API UClass* StaticClass<UStkAcousticMaterialFactory>()
	{
		return UStkAcousticMaterialFactory::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UStkAcousticMaterialFactory(Z_Construct_UClass_UStkAcousticMaterialFactory, &UStkAcousticMaterialFactory::StaticClass, TEXT("/Script/StkEditorModule"), TEXT("UStkAcousticMaterialFactory"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UStkAcousticMaterialFactory);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
