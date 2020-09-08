// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "StkGameModule/Private/StkGeometryComponent.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeStkGeometryComponent() {}
// Cross Module References
	STKGAMEMODULE_API UClass* Z_Construct_UClass_UStkGeometryComponent_NoRegister();
	STKGAMEMODULE_API UClass* Z_Construct_UClass_UStkGeometryComponent();
	ENGINE_API UClass* Z_Construct_UClass_USceneComponent();
	UPackage* Z_Construct_UPackage__Script_StkGameModule();
	ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
	STKGAMEMODULE_API UClass* Z_Construct_UClass_UStkAcousticData_NoRegister();
// End Cross Module References
	void UStkGeometryComponent::StaticRegisterNativesUStkGeometryComponent()
	{
	}
	UClass* Z_Construct_UClass_UStkGeometryComponent_NoRegister()
	{
		return UStkGeometryComponent::StaticClass();
	}
	struct Z_Construct_UClass_UStkGeometryComponent_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_OuterStaticMeshComponent_MetaData[];
#endif
		static const UE4CodeGen_Private::FSoftObjectPropertyParams NewProp_OuterStaticMeshComponent;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_AcousticData_MetaData[];
#endif
		static const UE4CodeGen_Private::FSoftObjectPropertyParams NewProp_AcousticData;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UStkGeometryComponent_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_USceneComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_StkGameModule,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UStkGeometryComponent_Statics::Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "SoundToolKit" },
		{ "Comment", "/// <summary>\n/// A component used to tag static meshes so that they become a part of acoustic geometry of the scene.\n/// </summary>\n" },
		{ "HideCategories", "Cooking Collision Rendering Tags Activation Physics LOD AssetUserData Trigger PhysicsVolume" },
		{ "IncludePath", "StkGeometryComponent.h" },
		{ "ModuleRelativePath", "Private/StkGeometryComponent.h" },
		{ "ToolTip", "<summary>\nA component used to tag static meshes so that they become a part of acoustic geometry of the scene.\n</summary>" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UStkGeometryComponent_Statics::NewProp_OuterStaticMeshComponent_MetaData[] = {
		{ "ModuleRelativePath", "Private/StkGeometryComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FSoftObjectPropertyParams Z_Construct_UClass_UStkGeometryComponent_Statics::NewProp_OuterStaticMeshComponent = { "OuterStaticMeshComponent", nullptr, (EPropertyFlags)0x0044000000080008, UE4CodeGen_Private::EPropertyGenFlags::SoftObject, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UStkGeometryComponent, OuterStaticMeshComponent), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UStkGeometryComponent_Statics::NewProp_OuterStaticMeshComponent_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UStkGeometryComponent_Statics::NewProp_OuterStaticMeshComponent_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UStkGeometryComponent_Statics::NewProp_AcousticData_MetaData[] = {
		{ "ModuleRelativePath", "Private/StkGeometryComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FSoftObjectPropertyParams Z_Construct_UClass_UStkGeometryComponent_Statics::NewProp_AcousticData = { "AcousticData", nullptr, (EPropertyFlags)0x0044000000000000, UE4CodeGen_Private::EPropertyGenFlags::SoftObject, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UStkGeometryComponent, AcousticData), Z_Construct_UClass_UStkAcousticData_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UStkGeometryComponent_Statics::NewProp_AcousticData_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UStkGeometryComponent_Statics::NewProp_AcousticData_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UStkGeometryComponent_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UStkGeometryComponent_Statics::NewProp_OuterStaticMeshComponent,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UStkGeometryComponent_Statics::NewProp_AcousticData,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UStkGeometryComponent_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UStkGeometryComponent>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UStkGeometryComponent_Statics::ClassParams = {
		&UStkGeometryComponent::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UStkGeometryComponent_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UStkGeometryComponent_Statics::PropPointers),
		0,
		0x00B000A4u,
		METADATA_PARAMS(Z_Construct_UClass_UStkGeometryComponent_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UStkGeometryComponent_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UStkGeometryComponent()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UStkGeometryComponent_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UStkGeometryComponent, 1913174462);
	template<> STKGAMEMODULE_API UClass* StaticClass<UStkGeometryComponent>()
	{
		return UStkGeometryComponent::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UStkGeometryComponent(Z_Construct_UClass_UStkGeometryComponent, &UStkGeometryComponent::StaticClass, TEXT("/Script/StkGameModule"), TEXT("UStkGeometryComponent"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UStkGeometryComponent);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
