// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "StkGameModule/Private/StkAcousticModel.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeStkAcousticModel() {}
// Cross Module References
	STKGAMEMODULE_API UClass* Z_Construct_UClass_UStkAcousticModel_NoRegister();
	STKGAMEMODULE_API UClass* Z_Construct_UClass_UStkAcousticModel();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	UPackage* Z_Construct_UPackage__Script_StkGameModule();
	ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
	LANDSCAPE_API UClass* Z_Construct_UClass_ALandscape_NoRegister();
// End Cross Module References
	void UStkAcousticModel::StaticRegisterNativesUStkAcousticModel()
	{
	}
	UClass* Z_Construct_UClass_UStkAcousticModel_NoRegister()
	{
		return UStkAcousticModel::StaticClass();
	}
	struct Z_Construct_UClass_UStkAcousticModel_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_StaticMeshComponents_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_StaticMeshComponents;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_StaticMeshComponents_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Landscapes_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_Landscapes;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Landscapes_Inner;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UStkAcousticModel_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_StkGameModule,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UStkAcousticModel_Statics::Class_MetaDataParams[] = {
		{ "ClassGroupNames", "SoundToolKit" },
		{ "Comment", "///\x09""Class representing acoustical model asset.\n" },
		{ "IncludePath", "StkAcousticModel.h" },
		{ "ModuleRelativePath", "Private/StkAcousticModel.h" },
		{ "ToolTip", "Class representing acoustical model asset." },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UStkAcousticModel_Statics::NewProp_StaticMeshComponents_MetaData[] = {
		{ "Category", "Model Content" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Private/StkAcousticModel.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UStkAcousticModel_Statics::NewProp_StaticMeshComponents = { "StaticMeshComponents", nullptr, (EPropertyFlags)0x0010008000022009, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UStkAcousticModel, StaticMeshComponents), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_UStkAcousticModel_Statics::NewProp_StaticMeshComponents_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UStkAcousticModel_Statics::NewProp_StaticMeshComponents_MetaData)) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UStkAcousticModel_Statics::NewProp_StaticMeshComponents_Inner = { "StaticMeshComponents", nullptr, (EPropertyFlags)0x00000000000a0008, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UStkAcousticModel_Statics::NewProp_Landscapes_MetaData[] = {
		{ "Category", "Model Content" },
		{ "ModuleRelativePath", "Private/StkAcousticModel.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UStkAcousticModel_Statics::NewProp_Landscapes = { "Landscapes", nullptr, (EPropertyFlags)0x0010000000022001, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UStkAcousticModel, Landscapes), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_UStkAcousticModel_Statics::NewProp_Landscapes_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UStkAcousticModel_Statics::NewProp_Landscapes_MetaData)) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UStkAcousticModel_Statics::NewProp_Landscapes_Inner = { "Landscapes", nullptr, (EPropertyFlags)0x0000000000020000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_ALandscape_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UStkAcousticModel_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UStkAcousticModel_Statics::NewProp_StaticMeshComponents,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UStkAcousticModel_Statics::NewProp_StaticMeshComponents_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UStkAcousticModel_Statics::NewProp_Landscapes,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UStkAcousticModel_Statics::NewProp_Landscapes_Inner,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UStkAcousticModel_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UStkAcousticModel>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UStkAcousticModel_Statics::ClassParams = {
		&UStkAcousticModel::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UStkAcousticModel_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UStkAcousticModel_Statics::PropPointers),
		0,
		0x009000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UStkAcousticModel_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UStkAcousticModel_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UStkAcousticModel()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UStkAcousticModel_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UStkAcousticModel, 2479394576);
	template<> STKGAMEMODULE_API UClass* StaticClass<UStkAcousticModel>()
	{
		return UStkAcousticModel::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UStkAcousticModel(Z_Construct_UClass_UStkAcousticModel, &UStkAcousticModel::StaticClass, TEXT("/Script/StkGameModule"), TEXT("UStkAcousticModel"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UStkAcousticModel);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
