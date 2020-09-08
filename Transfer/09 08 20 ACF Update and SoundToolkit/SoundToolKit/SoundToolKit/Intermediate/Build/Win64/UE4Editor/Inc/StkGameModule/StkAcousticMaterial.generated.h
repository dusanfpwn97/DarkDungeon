// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef STKGAMEMODULE_StkAcousticMaterial_generated_h
#error "StkAcousticMaterial.generated.h already included, missing '#pragma once' in StkAcousticMaterial.h"
#endif
#define STKGAMEMODULE_StkAcousticMaterial_generated_h

#define HostProject_Plugins_SoundToolKit_Source_StkGameModule_Private_StkAcousticMaterial_h_27_SPARSE_DATA
#define HostProject_Plugins_SoundToolKit_Source_StkGameModule_Private_StkAcousticMaterial_h_27_RPC_WRAPPERS
#define HostProject_Plugins_SoundToolKit_Source_StkGameModule_Private_StkAcousticMaterial_h_27_RPC_WRAPPERS_NO_PURE_DECLS
#define HostProject_Plugins_SoundToolKit_Source_StkGameModule_Private_StkAcousticMaterial_h_27_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUStkAcousticMaterial(); \
	friend struct Z_Construct_UClass_UStkAcousticMaterial_Statics; \
public: \
	DECLARE_CLASS(UStkAcousticMaterial, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/StkGameModule"), NO_API) \
	DECLARE_SERIALIZER(UStkAcousticMaterial)


#define HostProject_Plugins_SoundToolKit_Source_StkGameModule_Private_StkAcousticMaterial_h_27_INCLASS \
private: \
	static void StaticRegisterNativesUStkAcousticMaterial(); \
	friend struct Z_Construct_UClass_UStkAcousticMaterial_Statics; \
public: \
	DECLARE_CLASS(UStkAcousticMaterial, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/StkGameModule"), NO_API) \
	DECLARE_SERIALIZER(UStkAcousticMaterial)


#define HostProject_Plugins_SoundToolKit_Source_StkGameModule_Private_StkAcousticMaterial_h_27_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UStkAcousticMaterial(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UStkAcousticMaterial) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UStkAcousticMaterial); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UStkAcousticMaterial); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UStkAcousticMaterial(UStkAcousticMaterial&&); \
	NO_API UStkAcousticMaterial(const UStkAcousticMaterial&); \
public:


#define HostProject_Plugins_SoundToolKit_Source_StkGameModule_Private_StkAcousticMaterial_h_27_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UStkAcousticMaterial(UStkAcousticMaterial&&); \
	NO_API UStkAcousticMaterial(const UStkAcousticMaterial&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UStkAcousticMaterial); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UStkAcousticMaterial); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UStkAcousticMaterial)


#define HostProject_Plugins_SoundToolKit_Source_StkGameModule_Private_StkAcousticMaterial_h_27_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__Type() { return STRUCT_OFFSET(UStkAcousticMaterial, Type); }


#define HostProject_Plugins_SoundToolKit_Source_StkGameModule_Private_StkAcousticMaterial_h_24_PROLOG
#define HostProject_Plugins_SoundToolKit_Source_StkGameModule_Private_StkAcousticMaterial_h_27_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	HostProject_Plugins_SoundToolKit_Source_StkGameModule_Private_StkAcousticMaterial_h_27_PRIVATE_PROPERTY_OFFSET \
	HostProject_Plugins_SoundToolKit_Source_StkGameModule_Private_StkAcousticMaterial_h_27_SPARSE_DATA \
	HostProject_Plugins_SoundToolKit_Source_StkGameModule_Private_StkAcousticMaterial_h_27_RPC_WRAPPERS \
	HostProject_Plugins_SoundToolKit_Source_StkGameModule_Private_StkAcousticMaterial_h_27_INCLASS \
	HostProject_Plugins_SoundToolKit_Source_StkGameModule_Private_StkAcousticMaterial_h_27_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define HostProject_Plugins_SoundToolKit_Source_StkGameModule_Private_StkAcousticMaterial_h_27_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	HostProject_Plugins_SoundToolKit_Source_StkGameModule_Private_StkAcousticMaterial_h_27_PRIVATE_PROPERTY_OFFSET \
	HostProject_Plugins_SoundToolKit_Source_StkGameModule_Private_StkAcousticMaterial_h_27_SPARSE_DATA \
	HostProject_Plugins_SoundToolKit_Source_StkGameModule_Private_StkAcousticMaterial_h_27_RPC_WRAPPERS_NO_PURE_DECLS \
	HostProject_Plugins_SoundToolKit_Source_StkGameModule_Private_StkAcousticMaterial_h_27_INCLASS_NO_PURE_DECLS \
	HostProject_Plugins_SoundToolKit_Source_StkGameModule_Private_StkAcousticMaterial_h_27_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> STKGAMEMODULE_API UClass* StaticClass<class UStkAcousticMaterial>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID HostProject_Plugins_SoundToolKit_Source_StkGameModule_Private_StkAcousticMaterial_h


#define FOREACH_ENUM_ESTKMATERIALTYPE(op) \
	op(EStkMaterialType::Predefined) \
	op(EStkMaterialType::Custom) 

enum class EStkMaterialType : uint8;
template<> STKGAMEMODULE_API UEnum* StaticEnum<EStkMaterialType>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
