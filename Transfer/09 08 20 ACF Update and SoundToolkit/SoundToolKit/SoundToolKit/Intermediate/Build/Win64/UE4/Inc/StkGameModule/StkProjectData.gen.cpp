// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "StkGameModule/Private/StkProjectData.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeStkProjectData() {}
// Cross Module References
	STKGAMEMODULE_API UClass* Z_Construct_UClass_UStkProjectData_NoRegister();
	STKGAMEMODULE_API UClass* Z_Construct_UClass_UStkProjectData();
	ENGINE_API UClass* Z_Construct_UClass_UDataAsset();
	UPackage* Z_Construct_UPackage__Script_StkGameModule();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject_NoRegister();
	STKGAMEMODULE_API UClass* Z_Construct_UClass_UStkAcousticData_NoRegister();
// End Cross Module References
	void UStkProjectData::StaticRegisterNativesUStkProjectData()
	{
	}
	UClass* Z_Construct_UClass_UStkProjectData_NoRegister()
	{
		return UStkProjectData::StaticClass();
	}
	struct Z_Construct_UClass_UStkProjectData_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_StkArchetypesAcousticData_MetaData[];
#endif
		static const UE4CodeGen_Private::FMapPropertyParams NewProp_StkArchetypesAcousticData;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_StkArchetypesAcousticData_Key_KeyProp;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_StkArchetypesAcousticData_ValueProp;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UStkProjectData_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UDataAsset,
		(UObject* (*)())Z_Construct_UPackage__Script_StkGameModule,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UStkProjectData_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "StkProjectData.h" },
		{ "ModuleRelativePath", "Private/StkProjectData.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UStkProjectData_Statics::NewProp_StkArchetypesAcousticData_MetaData[] = {
		{ "ModuleRelativePath", "Private/StkProjectData.h" },
	};
#endif
	const UE4CodeGen_Private::FMapPropertyParams Z_Construct_UClass_UStkProjectData_Statics::NewProp_StkArchetypesAcousticData = { "StkArchetypesAcousticData", nullptr, (EPropertyFlags)0x0010000000000000, UE4CodeGen_Private::EPropertyGenFlags::Map, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UStkProjectData, StkArchetypesAcousticData), EMapPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_UStkProjectData_Statics::NewProp_StkArchetypesAcousticData_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UStkProjectData_Statics::NewProp_StkArchetypesAcousticData_MetaData)) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UStkProjectData_Statics::NewProp_StkArchetypesAcousticData_Key_KeyProp = { "StkArchetypesAcousticData_Key", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UStkProjectData_Statics::NewProp_StkArchetypesAcousticData_ValueProp = { "StkArchetypesAcousticData", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, 1, Z_Construct_UClass_UStkAcousticData_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UStkProjectData_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UStkProjectData_Statics::NewProp_StkArchetypesAcousticData,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UStkProjectData_Statics::NewProp_StkArchetypesAcousticData_Key_KeyProp,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UStkProjectData_Statics::NewProp_StkArchetypesAcousticData_ValueProp,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UStkProjectData_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UStkProjectData>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UStkProjectData_Statics::ClassParams = {
		&UStkProjectData::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UStkProjectData_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UStkProjectData_Statics::PropPointers),
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UStkProjectData_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UStkProjectData_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UStkProjectData()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UStkProjectData_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UStkProjectData, 3554762978);
	template<> STKGAMEMODULE_API UClass* StaticClass<UStkProjectData>()
	{
		return UStkProjectData::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UStkProjectData(Z_Construct_UClass_UStkProjectData, &UStkProjectData::StaticClass, TEXT("/Script/StkGameModule"), TEXT("UStkProjectData"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UStkProjectData);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
