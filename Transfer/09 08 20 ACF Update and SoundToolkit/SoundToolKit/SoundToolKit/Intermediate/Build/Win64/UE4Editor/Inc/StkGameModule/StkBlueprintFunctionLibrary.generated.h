// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FStkEffectCoefficients;
#ifdef STKGAMEMODULE_StkBlueprintFunctionLibrary_generated_h
#error "StkBlueprintFunctionLibrary.generated.h already included, missing '#pragma once' in StkBlueprintFunctionLibrary.h"
#endif
#define STKGAMEMODULE_StkBlueprintFunctionLibrary_generated_h

#define HostProject_Plugins_SoundToolKit_Source_StkGameModule_Public_StkBlueprintFunctionLibrary_h_14_SPARSE_DATA
#define HostProject_Plugins_SoundToolKit_Source_StkGameModule_Public_StkBlueprintFunctionLibrary_h_14_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execStkGetDampingCoefficients); \
	DECLARE_FUNCTION(execStkSetDampingCoefficients); \
	DECLARE_FUNCTION(execStkIsDampingEnabled); \
	DECLARE_FUNCTION(execStkDisableDamping); \
	DECLARE_FUNCTION(execStkEnableDamping); \
	DECLARE_FUNCTION(execStkGetSpeedOfSound); \
	DECLARE_FUNCTION(execStkSetSpeedOfSound); \
	DECLARE_FUNCTION(execStkIsDiffractionEnabled); \
	DECLARE_FUNCTION(execStkDisableDiffraction); \
	DECLARE_FUNCTION(execStkEnableDiffraction); \
	DECLARE_FUNCTION(execStkIsTransmissionEnabled); \
	DECLARE_FUNCTION(execStkDisableTransmission); \
	DECLARE_FUNCTION(execStkEnableTransmission); \
	DECLARE_FUNCTION(execStkIsReflectionEnabled); \
	DECLARE_FUNCTION(execStkDisableReflection); \
	DECLARE_FUNCTION(execStkEnableReflection); \
	DECLARE_FUNCTION(execStkIsAttenuationEnabled); \
	DECLARE_FUNCTION(execStkDisableAttenuation); \
	DECLARE_FUNCTION(execStkEnableAttenuation); \
	DECLARE_FUNCTION(execStkIsHrtfEnabled); \
	DECLARE_FUNCTION(execStkDisableHrtf); \
	DECLARE_FUNCTION(execStkEnableHrtf); \
	DECLARE_FUNCTION(execStkGetReverbVolume); \
	DECLARE_FUNCTION(execStkSetReverbVolume); \
	DECLARE_FUNCTION(execStkGetSpatialVolume); \
	DECLARE_FUNCTION(execStkSetSpatialVolume); \
	DECLARE_FUNCTION(execStkGetMasterVolume); \
	DECLARE_FUNCTION(execStkSetMasterVolume);


#define HostProject_Plugins_SoundToolKit_Source_StkGameModule_Public_StkBlueprintFunctionLibrary_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execStkGetDampingCoefficients); \
	DECLARE_FUNCTION(execStkSetDampingCoefficients); \
	DECLARE_FUNCTION(execStkIsDampingEnabled); \
	DECLARE_FUNCTION(execStkDisableDamping); \
	DECLARE_FUNCTION(execStkEnableDamping); \
	DECLARE_FUNCTION(execStkGetSpeedOfSound); \
	DECLARE_FUNCTION(execStkSetSpeedOfSound); \
	DECLARE_FUNCTION(execStkIsDiffractionEnabled); \
	DECLARE_FUNCTION(execStkDisableDiffraction); \
	DECLARE_FUNCTION(execStkEnableDiffraction); \
	DECLARE_FUNCTION(execStkIsTransmissionEnabled); \
	DECLARE_FUNCTION(execStkDisableTransmission); \
	DECLARE_FUNCTION(execStkEnableTransmission); \
	DECLARE_FUNCTION(execStkIsReflectionEnabled); \
	DECLARE_FUNCTION(execStkDisableReflection); \
	DECLARE_FUNCTION(execStkEnableReflection); \
	DECLARE_FUNCTION(execStkIsAttenuationEnabled); \
	DECLARE_FUNCTION(execStkDisableAttenuation); \
	DECLARE_FUNCTION(execStkEnableAttenuation); \
	DECLARE_FUNCTION(execStkIsHrtfEnabled); \
	DECLARE_FUNCTION(execStkDisableHrtf); \
	DECLARE_FUNCTION(execStkEnableHrtf); \
	DECLARE_FUNCTION(execStkGetReverbVolume); \
	DECLARE_FUNCTION(execStkSetReverbVolume); \
	DECLARE_FUNCTION(execStkGetSpatialVolume); \
	DECLARE_FUNCTION(execStkSetSpatialVolume); \
	DECLARE_FUNCTION(execStkGetMasterVolume); \
	DECLARE_FUNCTION(execStkSetMasterVolume);


#define HostProject_Plugins_SoundToolKit_Source_StkGameModule_Public_StkBlueprintFunctionLibrary_h_14_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUStkBlueprintFunctionLibrary(); \
	friend struct Z_Construct_UClass_UStkBlueprintFunctionLibrary_Statics; \
public: \
	DECLARE_CLASS(UStkBlueprintFunctionLibrary, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/StkGameModule"), NO_API) \
	DECLARE_SERIALIZER(UStkBlueprintFunctionLibrary)


#define HostProject_Plugins_SoundToolKit_Source_StkGameModule_Public_StkBlueprintFunctionLibrary_h_14_INCLASS \
private: \
	static void StaticRegisterNativesUStkBlueprintFunctionLibrary(); \
	friend struct Z_Construct_UClass_UStkBlueprintFunctionLibrary_Statics; \
public: \
	DECLARE_CLASS(UStkBlueprintFunctionLibrary, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/StkGameModule"), NO_API) \
	DECLARE_SERIALIZER(UStkBlueprintFunctionLibrary)


#define HostProject_Plugins_SoundToolKit_Source_StkGameModule_Public_StkBlueprintFunctionLibrary_h_14_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UStkBlueprintFunctionLibrary(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UStkBlueprintFunctionLibrary) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UStkBlueprintFunctionLibrary); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UStkBlueprintFunctionLibrary); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UStkBlueprintFunctionLibrary(UStkBlueprintFunctionLibrary&&); \
	NO_API UStkBlueprintFunctionLibrary(const UStkBlueprintFunctionLibrary&); \
public:


#define HostProject_Plugins_SoundToolKit_Source_StkGameModule_Public_StkBlueprintFunctionLibrary_h_14_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UStkBlueprintFunctionLibrary(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UStkBlueprintFunctionLibrary(UStkBlueprintFunctionLibrary&&); \
	NO_API UStkBlueprintFunctionLibrary(const UStkBlueprintFunctionLibrary&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UStkBlueprintFunctionLibrary); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UStkBlueprintFunctionLibrary); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UStkBlueprintFunctionLibrary)


#define HostProject_Plugins_SoundToolKit_Source_StkGameModule_Public_StkBlueprintFunctionLibrary_h_14_PRIVATE_PROPERTY_OFFSET
#define HostProject_Plugins_SoundToolKit_Source_StkGameModule_Public_StkBlueprintFunctionLibrary_h_11_PROLOG
#define HostProject_Plugins_SoundToolKit_Source_StkGameModule_Public_StkBlueprintFunctionLibrary_h_14_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	HostProject_Plugins_SoundToolKit_Source_StkGameModule_Public_StkBlueprintFunctionLibrary_h_14_PRIVATE_PROPERTY_OFFSET \
	HostProject_Plugins_SoundToolKit_Source_StkGameModule_Public_StkBlueprintFunctionLibrary_h_14_SPARSE_DATA \
	HostProject_Plugins_SoundToolKit_Source_StkGameModule_Public_StkBlueprintFunctionLibrary_h_14_RPC_WRAPPERS \
	HostProject_Plugins_SoundToolKit_Source_StkGameModule_Public_StkBlueprintFunctionLibrary_h_14_INCLASS \
	HostProject_Plugins_SoundToolKit_Source_StkGameModule_Public_StkBlueprintFunctionLibrary_h_14_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define HostProject_Plugins_SoundToolKit_Source_StkGameModule_Public_StkBlueprintFunctionLibrary_h_14_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	HostProject_Plugins_SoundToolKit_Source_StkGameModule_Public_StkBlueprintFunctionLibrary_h_14_PRIVATE_PROPERTY_OFFSET \
	HostProject_Plugins_SoundToolKit_Source_StkGameModule_Public_StkBlueprintFunctionLibrary_h_14_SPARSE_DATA \
	HostProject_Plugins_SoundToolKit_Source_StkGameModule_Public_StkBlueprintFunctionLibrary_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
	HostProject_Plugins_SoundToolKit_Source_StkGameModule_Public_StkBlueprintFunctionLibrary_h_14_INCLASS_NO_PURE_DECLS \
	HostProject_Plugins_SoundToolKit_Source_StkGameModule_Public_StkBlueprintFunctionLibrary_h_14_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> STKGAMEMODULE_API UClass* StaticClass<class UStkBlueprintFunctionLibrary>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID HostProject_Plugins_SoundToolKit_Source_StkGameModule_Public_StkBlueprintFunctionLibrary_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
