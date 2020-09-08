// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "StkEditorModule/Private/StkAcousticModelFactory.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeStkAcousticModelFactory() {}
// Cross Module References
	STKEDITORMODULE_API UClass* Z_Construct_UClass_UStkAcousticModelFactory_NoRegister();
	STKEDITORMODULE_API UClass* Z_Construct_UClass_UStkAcousticModelFactory();
	UNREALED_API UClass* Z_Construct_UClass_UFactory();
	UPackage* Z_Construct_UPackage__Script_StkEditorModule();
// End Cross Module References
	void UStkAcousticModelFactory::StaticRegisterNativesUStkAcousticModelFactory()
	{
	}
	UClass* Z_Construct_UClass_UStkAcousticModelFactory_NoRegister()
	{
		return UStkAcousticModelFactory::StaticClass();
	}
	struct Z_Construct_UClass_UStkAcousticModelFactory_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UStkAcousticModelFactory_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UFactory,
		(UObject* (*)())Z_Construct_UPackage__Script_StkEditorModule,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UStkAcousticModelFactory_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "StkAcousticModelFactory.h" },
		{ "ModuleRelativePath", "Private/StkAcousticModelFactory.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UStkAcousticModelFactory_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UStkAcousticModelFactory>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UStkAcousticModelFactory_Statics::ClassParams = {
		&UStkAcousticModelFactory::StaticClass,
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
		METADATA_PARAMS(Z_Construct_UClass_UStkAcousticModelFactory_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UStkAcousticModelFactory_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UStkAcousticModelFactory()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UStkAcousticModelFactory_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UStkAcousticModelFactory, 1816737378);
	template<> STKEDITORMODULE_API UClass* StaticClass<UStkAcousticModelFactory>()
	{
		return UStkAcousticModelFactory::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UStkAcousticModelFactory(Z_Construct_UClass_UStkAcousticModelFactory, &UStkAcousticModelFactory::StaticClass, TEXT("/Script/StkEditorModule"), TEXT("UStkAcousticModelFactory"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UStkAcousticModelFactory);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
