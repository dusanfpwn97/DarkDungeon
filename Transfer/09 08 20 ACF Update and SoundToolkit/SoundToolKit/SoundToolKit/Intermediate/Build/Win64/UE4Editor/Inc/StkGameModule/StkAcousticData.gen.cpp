// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "StkGameModule/Private/StkAcousticData.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeStkAcousticData() {}
// Cross Module References
	STKGAMEMODULE_API UClass* Z_Construct_UClass_UStkAcousticData_NoRegister();
	STKGAMEMODULE_API UClass* Z_Construct_UClass_UStkAcousticData();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	UPackage* Z_Construct_UPackage__Script_StkGameModule();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject_NoRegister();
	STKGAMEMODULE_API UClass* Z_Construct_UClass_UStkAcousticMaterial_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UStaticMesh_NoRegister();
	STKGAMEMODULE_API UClass* Z_Construct_UClass_UStkAcousticModel_NoRegister();
// End Cross Module References
	void UStkAcousticData::StaticRegisterNativesUStkAcousticData()
	{
	}
	UClass* Z_Construct_UClass_UStkAcousticData_NoRegister()
	{
		return UStkAcousticData::StaticClass();
	}
	struct Z_Construct_UClass_UStkAcousticData_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Object_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Object;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_AcousticMaterials_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_AcousticMaterials;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_AcousticMaterials_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_AcousticMesh_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_AcousticMesh;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_AcousticModel_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_AcousticModel;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bUseAsAcousticMesh_MetaData[];
#endif
		static void NewProp_bUseAsAcousticMesh_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bUseAsAcousticMesh;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UStkAcousticData_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_StkGameModule,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UStkAcousticData_Statics::Class_MetaDataParams[] = {
		{ "ClassGroupNames", "SoundToolKit" },
		{ "IncludePath", "StkAcousticData.h" },
		{ "ModuleRelativePath", "Private/StkAcousticData.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UStkAcousticData_Statics::NewProp_Object_MetaData[] = {
		{ "ModuleRelativePath", "Private/StkAcousticData.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UStkAcousticData_Statics::NewProp_Object = { "Object", nullptr, (EPropertyFlags)0x0040000000000000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UStkAcousticData, Object), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UStkAcousticData_Statics::NewProp_Object_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UStkAcousticData_Statics::NewProp_Object_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UStkAcousticData_Statics::NewProp_AcousticMaterials_MetaData[] = {
		{ "Category", "SoundToolKit" },
		{ "Comment", "/// Acoustic material associated with the acoustic mesh for this object per segment.\n/// If no acoustic material is selected (None) and 'Use as Acoustic Mesh' is checked, SoundToolKit's default material is used.\n" },
		{ "EditCondition", "bUseAsAcousticMesh" },
		{ "ModuleRelativePath", "Private/StkAcousticData.h" },
		{ "ToolTip", "Acoustic material associated with the acoustic mesh for this object per segment.\nIf no acoustic material is selected (None) and 'Use as Acoustic Mesh' is checked, SoundToolKit's default material is used." },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UStkAcousticData_Statics::NewProp_AcousticMaterials = { "AcousticMaterials", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UStkAcousticData, AcousticMaterials), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_UStkAcousticData_Statics::NewProp_AcousticMaterials_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UStkAcousticData_Statics::NewProp_AcousticMaterials_MetaData)) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UStkAcousticData_Statics::NewProp_AcousticMaterials_Inner = { "AcousticMaterials", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_UStkAcousticMaterial_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UStkAcousticData_Statics::NewProp_AcousticMesh_MetaData[] = {
		{ "Category", "SoundToolKit" },
		{ "Comment", "/// A static mesh used as a simplified acoustic geometry representation for this object inside SoundToolKit engine.\n/// If no acoustic mesh is selected (None) and 'Use as Acoustic Mesh' is checked, this object's collision mesh is used as acoustic geometry inside SoundToolKit engine.\n" },
		{ "EditCondition", "bUseAsAcousticMesh" },
		{ "ModuleRelativePath", "Private/StkAcousticData.h" },
		{ "ToolTip", "A static mesh used as a simplified acoustic geometry representation for this object inside SoundToolKit engine.\nIf no acoustic mesh is selected (None) and 'Use as Acoustic Mesh' is checked, this object's collision mesh is used as acoustic geometry inside SoundToolKit engine." },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UStkAcousticData_Statics::NewProp_AcousticMesh = { "AcousticMesh", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UStkAcousticData, AcousticMesh), Z_Construct_UClass_UStaticMesh_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UStkAcousticData_Statics::NewProp_AcousticMesh_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UStkAcousticData_Statics::NewProp_AcousticMesh_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UStkAcousticData_Statics::NewProp_AcousticModel_MetaData[] = {
		{ "Category", "SoundToolKit" },
		{ "Comment", "/// Model is an abstraction of a group of acoustic meshes (StaticMesh & Landscape actors marked to be used as acoustic meshes).\n/// StaticMeshComponents' and Landscapes' meshes with the same StkAcousticModel assigned are loaded and unloaded as one entity into the SoundToolKit engine.\n/// \n/// All actors without StkAcousticModel specified (None) are grouped as single default model inside SoundToolKit.\n" },
		{ "EditCondition", "bUseAsAcousticMesh" },
		{ "ModuleRelativePath", "Private/StkAcousticData.h" },
		{ "ToolTip", "Model is an abstraction of a group of acoustic meshes (StaticMesh & Landscape actors marked to be used as acoustic meshes).\nStaticMeshComponents' and Landscapes' meshes with the same StkAcousticModel assigned are loaded and unloaded as one entity into the SoundToolKit engine.\n\nAll actors without StkAcousticModel specified (None) are grouped as single default model inside SoundToolKit." },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UStkAcousticData_Statics::NewProp_AcousticModel = { "AcousticModel", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UStkAcousticData, AcousticModel), Z_Construct_UClass_UStkAcousticModel_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UStkAcousticData_Statics::NewProp_AcousticModel_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UStkAcousticData_Statics::NewProp_AcousticModel_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UStkAcousticData_Statics::NewProp_bUseAsAcousticMesh_MetaData[] = {
		{ "Category", "SoundToolKit" },
		{ "Comment", "/// Whether or not use this object as acoustic mesh inside SoundToolKit engine.\n" },
		{ "ModuleRelativePath", "Private/StkAcousticData.h" },
		{ "ToolTip", "Whether or not use this object as acoustic mesh inside SoundToolKit engine." },
	};
#endif
	void Z_Construct_UClass_UStkAcousticData_Statics::NewProp_bUseAsAcousticMesh_SetBit(void* Obj)
	{
		((UStkAcousticData*)Obj)->bUseAsAcousticMesh = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UStkAcousticData_Statics::NewProp_bUseAsAcousticMesh = { "bUseAsAcousticMesh", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UStkAcousticData), &Z_Construct_UClass_UStkAcousticData_Statics::NewProp_bUseAsAcousticMesh_SetBit, METADATA_PARAMS(Z_Construct_UClass_UStkAcousticData_Statics::NewProp_bUseAsAcousticMesh_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UStkAcousticData_Statics::NewProp_bUseAsAcousticMesh_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UStkAcousticData_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UStkAcousticData_Statics::NewProp_Object,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UStkAcousticData_Statics::NewProp_AcousticMaterials,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UStkAcousticData_Statics::NewProp_AcousticMaterials_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UStkAcousticData_Statics::NewProp_AcousticMesh,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UStkAcousticData_Statics::NewProp_AcousticModel,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UStkAcousticData_Statics::NewProp_bUseAsAcousticMesh,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UStkAcousticData_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UStkAcousticData>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UStkAcousticData_Statics::ClassParams = {
		&UStkAcousticData::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UStkAcousticData_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UStkAcousticData_Statics::PropPointers),
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UStkAcousticData_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UStkAcousticData_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UStkAcousticData()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UStkAcousticData_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UStkAcousticData, 626951842);
	template<> STKGAMEMODULE_API UClass* StaticClass<UStkAcousticData>()
	{
		return UStkAcousticData::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UStkAcousticData(Z_Construct_UClass_UStkAcousticData, &UStkAcousticData::StaticClass, TEXT("/Script/StkGameModule"), TEXT("UStkAcousticData"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UStkAcousticData);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
