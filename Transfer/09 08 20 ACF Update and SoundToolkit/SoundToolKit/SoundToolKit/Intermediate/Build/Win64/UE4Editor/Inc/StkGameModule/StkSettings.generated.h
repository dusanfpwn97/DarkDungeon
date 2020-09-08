// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef STKGAMEMODULE_StkSettings_generated_h
#error "StkSettings.generated.h already included, missing '#pragma once' in StkSettings.h"
#endif
#define STKGAMEMODULE_StkSettings_generated_h

#define HostProject_Plugins_SoundToolKit_Source_StkGameModule_Private_StkSettings_h_33_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FStkSetting_Statics; \
	static class UScriptStruct* StaticStruct();


template<> STKGAMEMODULE_API UScriptStruct* StaticStruct<struct FStkSetting>();

#define HostProject_Plugins_SoundToolKit_Source_StkGameModule_Private_StkSettings_h_83_SPARSE_DATA
#define HostProject_Plugins_SoundToolKit_Source_StkGameModule_Private_StkSettings_h_83_RPC_WRAPPERS
#define HostProject_Plugins_SoundToolKit_Source_StkGameModule_Private_StkSettings_h_83_RPC_WRAPPERS_NO_PURE_DECLS
#define HostProject_Plugins_SoundToolKit_Source_StkGameModule_Private_StkSettings_h_83_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUStkSettings(); \
	friend struct Z_Construct_UClass_UStkSettings_Statics; \
public: \
	DECLARE_CLASS(UStkSettings, UObject, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/StkGameModule"), NO_API) \
	DECLARE_SERIALIZER(UStkSettings) \
	static const TCHAR* StaticConfigName() {return TEXT("Game");} \



#define HostProject_Plugins_SoundToolKit_Source_StkGameModule_Private_StkSettings_h_83_INCLASS \
private: \
	static void StaticRegisterNativesUStkSettings(); \
	friend struct Z_Construct_UClass_UStkSettings_Statics; \
public: \
	DECLARE_CLASS(UStkSettings, UObject, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/StkGameModule"), NO_API) \
	DECLARE_SERIALIZER(UStkSettings) \
	static const TCHAR* StaticConfigName() {return TEXT("Game");} \



#define HostProject_Plugins_SoundToolKit_Source_StkGameModule_Private_StkSettings_h_83_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UStkSettings(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UStkSettings) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UStkSettings); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UStkSettings); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UStkSettings(UStkSettings&&); \
	NO_API UStkSettings(const UStkSettings&); \
public:


#define HostProject_Plugins_SoundToolKit_Source_StkGameModule_Private_StkSettings_h_83_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UStkSettings(UStkSettings&&); \
	NO_API UStkSettings(const UStkSettings&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UStkSettings); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UStkSettings); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UStkSettings)


#define HostProject_Plugins_SoundToolKit_Source_StkGameModule_Private_StkSettings_h_83_PRIVATE_PROPERTY_OFFSET
#define HostProject_Plugins_SoundToolKit_Source_StkGameModule_Private_StkSettings_h_80_PROLOG
#define HostProject_Plugins_SoundToolKit_Source_StkGameModule_Private_StkSettings_h_83_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	HostProject_Plugins_SoundToolKit_Source_StkGameModule_Private_StkSettings_h_83_PRIVATE_PROPERTY_OFFSET \
	HostProject_Plugins_SoundToolKit_Source_StkGameModule_Private_StkSettings_h_83_SPARSE_DATA \
	HostProject_Plugins_SoundToolKit_Source_StkGameModule_Private_StkSettings_h_83_RPC_WRAPPERS \
	HostProject_Plugins_SoundToolKit_Source_StkGameModule_Private_StkSettings_h_83_INCLASS \
	HostProject_Plugins_SoundToolKit_Source_StkGameModule_Private_StkSettings_h_83_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define HostProject_Plugins_SoundToolKit_Source_StkGameModule_Private_StkSettings_h_83_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	HostProject_Plugins_SoundToolKit_Source_StkGameModule_Private_StkSettings_h_83_PRIVATE_PROPERTY_OFFSET \
	HostProject_Plugins_SoundToolKit_Source_StkGameModule_Private_StkSettings_h_83_SPARSE_DATA \
	HostProject_Plugins_SoundToolKit_Source_StkGameModule_Private_StkSettings_h_83_RPC_WRAPPERS_NO_PURE_DECLS \
	HostProject_Plugins_SoundToolKit_Source_StkGameModule_Private_StkSettings_h_83_INCLASS_NO_PURE_DECLS \
	HostProject_Plugins_SoundToolKit_Source_StkGameModule_Private_StkSettings_h_83_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> STKGAMEMODULE_API UClass* StaticClass<class UStkSettings>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID HostProject_Plugins_SoundToolKit_Source_StkGameModule_Private_StkSettings_h


#define FOREACH_ENUM_ESTKSETTINGTYPE(op) \
	op(EStkSettingType::StkSettingType_Boolean) \
	op(EStkSettingType::StkSettingType_Enumeration) \
	op(EStkSettingType::StkSettingType_Integer) \
	op(EStkSettingType::StkSettingType_Float) \
	op(EStkSettingType::StkSettingType_ListOfIntegers) \
	op(EStkSettingType::StkSettingType_ListOfFloats) 

enum class EStkSettingType : uint8;
template<> STKGAMEMODULE_API UEnum* StaticEnum<EStkSettingType>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
