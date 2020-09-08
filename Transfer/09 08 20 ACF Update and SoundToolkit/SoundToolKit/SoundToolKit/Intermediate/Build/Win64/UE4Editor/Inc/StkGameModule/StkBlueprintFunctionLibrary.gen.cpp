// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "StkGameModule/Public/StkBlueprintFunctionLibrary.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeStkBlueprintFunctionLibrary() {}
// Cross Module References
	STKGAMEMODULE_API UClass* Z_Construct_UClass_UStkBlueprintFunctionLibrary_NoRegister();
	STKGAMEMODULE_API UClass* Z_Construct_UClass_UStkBlueprintFunctionLibrary();
	ENGINE_API UClass* Z_Construct_UClass_UBlueprintFunctionLibrary();
	UPackage* Z_Construct_UPackage__Script_StkGameModule();
	STKGAMEMODULE_API UScriptStruct* Z_Construct_UScriptStruct_FStkEffectCoefficients();
// End Cross Module References
	DEFINE_FUNCTION(UStkBlueprintFunctionLibrary::execStkGetDampingCoefficients)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FStkEffectCoefficients*)Z_Param__Result=UStkBlueprintFunctionLibrary::StkGetDampingCoefficients();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UStkBlueprintFunctionLibrary::execStkSetDampingCoefficients)
	{
		P_GET_STRUCT(FStkEffectCoefficients,Z_Param_DampingCoefficients);
		P_FINISH;
		P_NATIVE_BEGIN;
		UStkBlueprintFunctionLibrary::StkSetDampingCoefficients(Z_Param_DampingCoefficients);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UStkBlueprintFunctionLibrary::execStkIsDampingEnabled)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=UStkBlueprintFunctionLibrary::StkIsDampingEnabled();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UStkBlueprintFunctionLibrary::execStkDisableDamping)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		UStkBlueprintFunctionLibrary::StkDisableDamping();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UStkBlueprintFunctionLibrary::execStkEnableDamping)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		UStkBlueprintFunctionLibrary::StkEnableDamping();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UStkBlueprintFunctionLibrary::execStkGetSpeedOfSound)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(float*)Z_Param__Result=UStkBlueprintFunctionLibrary::StkGetSpeedOfSound();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UStkBlueprintFunctionLibrary::execStkSetSpeedOfSound)
	{
		P_GET_PROPERTY(FFloatProperty,Z_Param_SpeedOfSound);
		P_FINISH;
		P_NATIVE_BEGIN;
		UStkBlueprintFunctionLibrary::StkSetSpeedOfSound(Z_Param_SpeedOfSound);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UStkBlueprintFunctionLibrary::execStkIsDiffractionEnabled)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=UStkBlueprintFunctionLibrary::StkIsDiffractionEnabled();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UStkBlueprintFunctionLibrary::execStkDisableDiffraction)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		UStkBlueprintFunctionLibrary::StkDisableDiffraction();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UStkBlueprintFunctionLibrary::execStkEnableDiffraction)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		UStkBlueprintFunctionLibrary::StkEnableDiffraction();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UStkBlueprintFunctionLibrary::execStkIsTransmissionEnabled)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=UStkBlueprintFunctionLibrary::StkIsTransmissionEnabled();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UStkBlueprintFunctionLibrary::execStkDisableTransmission)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		UStkBlueprintFunctionLibrary::StkDisableTransmission();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UStkBlueprintFunctionLibrary::execStkEnableTransmission)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		UStkBlueprintFunctionLibrary::StkEnableTransmission();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UStkBlueprintFunctionLibrary::execStkIsReflectionEnabled)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=UStkBlueprintFunctionLibrary::StkIsReflectionEnabled();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UStkBlueprintFunctionLibrary::execStkDisableReflection)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		UStkBlueprintFunctionLibrary::StkDisableReflection();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UStkBlueprintFunctionLibrary::execStkEnableReflection)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		UStkBlueprintFunctionLibrary::StkEnableReflection();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UStkBlueprintFunctionLibrary::execStkIsAttenuationEnabled)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=UStkBlueprintFunctionLibrary::StkIsAttenuationEnabled();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UStkBlueprintFunctionLibrary::execStkDisableAttenuation)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		UStkBlueprintFunctionLibrary::StkDisableAttenuation();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UStkBlueprintFunctionLibrary::execStkEnableAttenuation)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		UStkBlueprintFunctionLibrary::StkEnableAttenuation();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UStkBlueprintFunctionLibrary::execStkIsHrtfEnabled)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=UStkBlueprintFunctionLibrary::StkIsHrtfEnabled();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UStkBlueprintFunctionLibrary::execStkDisableHrtf)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		UStkBlueprintFunctionLibrary::StkDisableHrtf();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UStkBlueprintFunctionLibrary::execStkEnableHrtf)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		UStkBlueprintFunctionLibrary::StkEnableHrtf();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UStkBlueprintFunctionLibrary::execStkGetReverbVolume)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(float*)Z_Param__Result=UStkBlueprintFunctionLibrary::StkGetReverbVolume();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UStkBlueprintFunctionLibrary::execStkSetReverbVolume)
	{
		P_GET_PROPERTY(FFloatProperty,Z_Param_Volume);
		P_FINISH;
		P_NATIVE_BEGIN;
		UStkBlueprintFunctionLibrary::StkSetReverbVolume(Z_Param_Volume);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UStkBlueprintFunctionLibrary::execStkGetSpatialVolume)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(float*)Z_Param__Result=UStkBlueprintFunctionLibrary::StkGetSpatialVolume();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UStkBlueprintFunctionLibrary::execStkSetSpatialVolume)
	{
		P_GET_PROPERTY(FFloatProperty,Z_Param_Volume);
		P_FINISH;
		P_NATIVE_BEGIN;
		UStkBlueprintFunctionLibrary::StkSetSpatialVolume(Z_Param_Volume);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UStkBlueprintFunctionLibrary::execStkGetMasterVolume)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(float*)Z_Param__Result=UStkBlueprintFunctionLibrary::StkGetMasterVolume();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UStkBlueprintFunctionLibrary::execStkSetMasterVolume)
	{
		P_GET_PROPERTY(FFloatProperty,Z_Param_Volume);
		P_FINISH;
		P_NATIVE_BEGIN;
		UStkBlueprintFunctionLibrary::StkSetMasterVolume(Z_Param_Volume);
		P_NATIVE_END;
	}
	void UStkBlueprintFunctionLibrary::StaticRegisterNativesUStkBlueprintFunctionLibrary()
	{
		UClass* Class = UStkBlueprintFunctionLibrary::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "StkDisableAttenuation", &UStkBlueprintFunctionLibrary::execStkDisableAttenuation },
			{ "StkDisableDamping", &UStkBlueprintFunctionLibrary::execStkDisableDamping },
			{ "StkDisableDiffraction", &UStkBlueprintFunctionLibrary::execStkDisableDiffraction },
			{ "StkDisableHrtf", &UStkBlueprintFunctionLibrary::execStkDisableHrtf },
			{ "StkDisableReflection", &UStkBlueprintFunctionLibrary::execStkDisableReflection },
			{ "StkDisableTransmission", &UStkBlueprintFunctionLibrary::execStkDisableTransmission },
			{ "StkEnableAttenuation", &UStkBlueprintFunctionLibrary::execStkEnableAttenuation },
			{ "StkEnableDamping", &UStkBlueprintFunctionLibrary::execStkEnableDamping },
			{ "StkEnableDiffraction", &UStkBlueprintFunctionLibrary::execStkEnableDiffraction },
			{ "StkEnableHrtf", &UStkBlueprintFunctionLibrary::execStkEnableHrtf },
			{ "StkEnableReflection", &UStkBlueprintFunctionLibrary::execStkEnableReflection },
			{ "StkEnableTransmission", &UStkBlueprintFunctionLibrary::execStkEnableTransmission },
			{ "StkGetDampingCoefficients", &UStkBlueprintFunctionLibrary::execStkGetDampingCoefficients },
			{ "StkGetMasterVolume", &UStkBlueprintFunctionLibrary::execStkGetMasterVolume },
			{ "StkGetReverbVolume", &UStkBlueprintFunctionLibrary::execStkGetReverbVolume },
			{ "StkGetSpatialVolume", &UStkBlueprintFunctionLibrary::execStkGetSpatialVolume },
			{ "StkGetSpeedOfSound", &UStkBlueprintFunctionLibrary::execStkGetSpeedOfSound },
			{ "StkIsAttenuationEnabled", &UStkBlueprintFunctionLibrary::execStkIsAttenuationEnabled },
			{ "StkIsDampingEnabled", &UStkBlueprintFunctionLibrary::execStkIsDampingEnabled },
			{ "StkIsDiffractionEnabled", &UStkBlueprintFunctionLibrary::execStkIsDiffractionEnabled },
			{ "StkIsHrtfEnabled", &UStkBlueprintFunctionLibrary::execStkIsHrtfEnabled },
			{ "StkIsReflectionEnabled", &UStkBlueprintFunctionLibrary::execStkIsReflectionEnabled },
			{ "StkIsTransmissionEnabled", &UStkBlueprintFunctionLibrary::execStkIsTransmissionEnabled },
			{ "StkSetDampingCoefficients", &UStkBlueprintFunctionLibrary::execStkSetDampingCoefficients },
			{ "StkSetMasterVolume", &UStkBlueprintFunctionLibrary::execStkSetMasterVolume },
			{ "StkSetReverbVolume", &UStkBlueprintFunctionLibrary::execStkSetReverbVolume },
			{ "StkSetSpatialVolume", &UStkBlueprintFunctionLibrary::execStkSetSpatialVolume },
			{ "StkSetSpeedOfSound", &UStkBlueprintFunctionLibrary::execStkSetSpeedOfSound },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkDisableAttenuation_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkDisableAttenuation_Statics::Function_MetaDataParams[] = {
		{ "Category", "Spatial Effects" },
		{ "Comment", "/// Disables global attenuation of sound with distance on the scene for all sound sources processed by SoundToolKit.\n" },
		{ "ModuleRelativePath", "Public/StkBlueprintFunctionLibrary.h" },
		{ "ToolTip", "Disables global attenuation of sound with distance on the scene for all sound sources processed by SoundToolKit." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkDisableAttenuation_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UStkBlueprintFunctionLibrary, nullptr, "StkDisableAttenuation", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04042401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkDisableAttenuation_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkDisableAttenuation_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkDisableAttenuation()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkDisableAttenuation_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkDisableDamping_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkDisableDamping_Statics::Function_MetaDataParams[] = {
		{ "Category", "Acoustic Medium" },
		{ "Comment", "/// Disables attenuation due to acoustic medium viscosity on the scene for all sound sources processed by SoundToolKit.\n" },
		{ "ModuleRelativePath", "Public/StkBlueprintFunctionLibrary.h" },
		{ "ToolTip", "Disables attenuation due to acoustic medium viscosity on the scene for all sound sources processed by SoundToolKit." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkDisableDamping_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UStkBlueprintFunctionLibrary, nullptr, "StkDisableDamping", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04042401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkDisableDamping_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkDisableDamping_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkDisableDamping()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkDisableDamping_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkDisableDiffraction_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkDisableDiffraction_Statics::Function_MetaDataParams[] = {
		{ "Category", "Occlusion Effects" },
		{ "Comment", "/// Disables global diffraction of sound on edges on the scene for all sound sources processed by SoundToolKit.\n/// This disables diffraction effect for the entire scene, for all sound sources, even if diffraction is enabled for particular sound source in StkOcclusionSourceSettings.\n" },
		{ "ModuleRelativePath", "Public/StkBlueprintFunctionLibrary.h" },
		{ "ToolTip", "Disables global diffraction of sound on edges on the scene for all sound sources processed by SoundToolKit.\nThis disables diffraction effect for the entire scene, for all sound sources, even if diffraction is enabled for particular sound source in StkOcclusionSourceSettings." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkDisableDiffraction_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UStkBlueprintFunctionLibrary, nullptr, "StkDisableDiffraction", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04042401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkDisableDiffraction_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkDisableDiffraction_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkDisableDiffraction()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkDisableDiffraction_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkDisableHrtf_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkDisableHrtf_Statics::Function_MetaDataParams[] = {
		{ "Category", "Spatial Effects" },
		{ "Comment", "/// Disables global HRTF spatialization on the scene for all sound sources processed by SoundToolKit.\n/// This disables HRTF for the entire scene, for all sound sources, even if HRTF is enabled for particular sound source in StkSpatialSourceSettings.\n" },
		{ "ModuleRelativePath", "Public/StkBlueprintFunctionLibrary.h" },
		{ "ToolTip", "Disables global HRTF spatialization on the scene for all sound sources processed by SoundToolKit.\nThis disables HRTF for the entire scene, for all sound sources, even if HRTF is enabled for particular sound source in StkSpatialSourceSettings." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkDisableHrtf_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UStkBlueprintFunctionLibrary, nullptr, "StkDisableHrtf", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04042401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkDisableHrtf_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkDisableHrtf_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkDisableHrtf()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkDisableHrtf_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkDisableReflection_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkDisableReflection_Statics::Function_MetaDataParams[] = {
		{ "Category", "Occlusion Effects" },
		{ "Comment", "/// Disables global specular reflection of sound from obstacles on the scene for all sound sources processed by SoundToolKit.\n/// This disables reflection effect for the entire scene, for all sound sources, even if reflection is enabled for particular sound source in StkOcclusionSourceSettings.\n" },
		{ "ModuleRelativePath", "Public/StkBlueprintFunctionLibrary.h" },
		{ "ToolTip", "Disables global specular reflection of sound from obstacles on the scene for all sound sources processed by SoundToolKit.\nThis disables reflection effect for the entire scene, for all sound sources, even if reflection is enabled for particular sound source in StkOcclusionSourceSettings." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkDisableReflection_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UStkBlueprintFunctionLibrary, nullptr, "StkDisableReflection", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04042401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkDisableReflection_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkDisableReflection_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkDisableReflection()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkDisableReflection_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkDisableTransmission_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkDisableTransmission_Statics::Function_MetaDataParams[] = {
		{ "Category", "Occlusion Effects" },
		{ "Comment", "/// Disables global transmission of sound through obstacles on the scene for all sound sources processed by SoundToolKit.\n/// This disables transmission effect for the entire scene, for all sound sources, even if transmission is enabled for particular sound source in StkOcclusionSourceSettings.\n" },
		{ "ModuleRelativePath", "Public/StkBlueprintFunctionLibrary.h" },
		{ "ToolTip", "Disables global transmission of sound through obstacles on the scene for all sound sources processed by SoundToolKit.\nThis disables transmission effect for the entire scene, for all sound sources, even if transmission is enabled for particular sound source in StkOcclusionSourceSettings." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkDisableTransmission_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UStkBlueprintFunctionLibrary, nullptr, "StkDisableTransmission", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04042401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkDisableTransmission_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkDisableTransmission_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkDisableTransmission()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkDisableTransmission_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkEnableAttenuation_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkEnableAttenuation_Statics::Function_MetaDataParams[] = {
		{ "Category", "Spatial Effects" },
		{ "Comment", "/// Enables global attenuation of sound with distance on the scene for all sound sources processed by SoundToolKit.\n" },
		{ "ModuleRelativePath", "Public/StkBlueprintFunctionLibrary.h" },
		{ "ToolTip", "Enables global attenuation of sound with distance on the scene for all sound sources processed by SoundToolKit." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkEnableAttenuation_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UStkBlueprintFunctionLibrary, nullptr, "StkEnableAttenuation", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04042401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkEnableAttenuation_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkEnableAttenuation_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkEnableAttenuation()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkEnableAttenuation_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkEnableDamping_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkEnableDamping_Statics::Function_MetaDataParams[] = {
		{ "Category", "Acoustic Medium" },
		{ "Comment", "/// Enables attenuation due to acoustic medium viscosity on the scene for all sound sources processed by SoundToolKit.\n" },
		{ "ModuleRelativePath", "Public/StkBlueprintFunctionLibrary.h" },
		{ "ToolTip", "Enables attenuation due to acoustic medium viscosity on the scene for all sound sources processed by SoundToolKit." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkEnableDamping_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UStkBlueprintFunctionLibrary, nullptr, "StkEnableDamping", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04042401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkEnableDamping_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkEnableDamping_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkEnableDamping()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkEnableDamping_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkEnableDiffraction_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkEnableDiffraction_Statics::Function_MetaDataParams[] = {
		{ "Category", "Occlusion Effects" },
		{ "Comment", "/// Enables global diffraction of sound on edges on the scene for all sound sources processed by SoundToolKit.\n/// The diffraction effect is still disabled for sound sources that have this flag disabled in StkOcclusionSourceSettings.\n" },
		{ "ModuleRelativePath", "Public/StkBlueprintFunctionLibrary.h" },
		{ "ToolTip", "Enables global diffraction of sound on edges on the scene for all sound sources processed by SoundToolKit.\nThe diffraction effect is still disabled for sound sources that have this flag disabled in StkOcclusionSourceSettings." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkEnableDiffraction_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UStkBlueprintFunctionLibrary, nullptr, "StkEnableDiffraction", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04042401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkEnableDiffraction_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkEnableDiffraction_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkEnableDiffraction()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkEnableDiffraction_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkEnableHrtf_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkEnableHrtf_Statics::Function_MetaDataParams[] = {
		{ "Category", "Spatial Effects" },
		{ "Comment", "/// Enables global HRTF spatialization on the scene for all sound sources processed by SoundToolKit.\n/// The HRTF effect is still disabled for sound sources that have this flag disabled in StkSpatialSourceSettings.\n" },
		{ "ModuleRelativePath", "Public/StkBlueprintFunctionLibrary.h" },
		{ "ToolTip", "Enables global HRTF spatialization on the scene for all sound sources processed by SoundToolKit.\nThe HRTF effect is still disabled for sound sources that have this flag disabled in StkSpatialSourceSettings." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkEnableHrtf_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UStkBlueprintFunctionLibrary, nullptr, "StkEnableHrtf", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04042401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkEnableHrtf_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkEnableHrtf_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkEnableHrtf()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkEnableHrtf_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkEnableReflection_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkEnableReflection_Statics::Function_MetaDataParams[] = {
		{ "Category", "Occlusion Effects" },
		{ "Comment", "/// Enables global specular reflection of sound from obstacles on the scene for all sound sources processed by SoundToolKit.\n/// The reflection effect is still disabled for sound sources that have this flag disabled in StkOcclusionSourceSettings.\n" },
		{ "ModuleRelativePath", "Public/StkBlueprintFunctionLibrary.h" },
		{ "ToolTip", "Enables global specular reflection of sound from obstacles on the scene for all sound sources processed by SoundToolKit.\nThe reflection effect is still disabled for sound sources that have this flag disabled in StkOcclusionSourceSettings." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkEnableReflection_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UStkBlueprintFunctionLibrary, nullptr, "StkEnableReflection", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04042401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkEnableReflection_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkEnableReflection_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkEnableReflection()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkEnableReflection_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkEnableTransmission_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkEnableTransmission_Statics::Function_MetaDataParams[] = {
		{ "Category", "Occlusion Effects" },
		{ "Comment", "/// Enables global transmission of sound through obstacles on the scene for all sound sources processed by SoundToolKit.\n/// The transmission effect is still disabled for sound sources that have this flag disabled in StkOcclusionSourceSettings.\n" },
		{ "ModuleRelativePath", "Public/StkBlueprintFunctionLibrary.h" },
		{ "ToolTip", "Enables global transmission of sound through obstacles on the scene for all sound sources processed by SoundToolKit.\nThe transmission effect is still disabled for sound sources that have this flag disabled in StkOcclusionSourceSettings." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkEnableTransmission_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UStkBlueprintFunctionLibrary, nullptr, "StkEnableTransmission", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04042401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkEnableTransmission_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkEnableTransmission_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkEnableTransmission()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkEnableTransmission_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkGetDampingCoefficients_Statics
	{
		struct StkBlueprintFunctionLibrary_eventStkGetDampingCoefficients_Parms
		{
			FStkEffectCoefficients ReturnValue;
		};
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkGetDampingCoefficients_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(StkBlueprintFunctionLibrary_eventStkGetDampingCoefficients_Parms, ReturnValue), Z_Construct_UScriptStruct_FStkEffectCoefficients, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkGetDampingCoefficients_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkGetDampingCoefficients_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkGetDampingCoefficients_Statics::Function_MetaDataParams[] = {
		{ "Category", "Acoustic Medium" },
		{ "Comment", "/// Gets the coefficients for attenuation due to medium viscosity on the scene for all sound sources processed by SoundToolKit.\n/// Coefficient value for each band is in range [0, 1].\n" },
		{ "ModuleRelativePath", "Public/StkBlueprintFunctionLibrary.h" },
		{ "ToolTip", "Gets the coefficients for attenuation due to medium viscosity on the scene for all sound sources processed by SoundToolKit.\nCoefficient value for each band is in range [0, 1]." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkGetDampingCoefficients_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UStkBlueprintFunctionLibrary, nullptr, "StkGetDampingCoefficients", nullptr, nullptr, sizeof(StkBlueprintFunctionLibrary_eventStkGetDampingCoefficients_Parms), Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkGetDampingCoefficients_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkGetDampingCoefficients_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04042401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkGetDampingCoefficients_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkGetDampingCoefficients_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkGetDampingCoefficients()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkGetDampingCoefficients_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkGetMasterVolume_Statics
	{
		struct StkBlueprintFunctionLibrary_eventStkGetMasterVolume_Parms
		{
			float ReturnValue;
		};
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkGetMasterVolume_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(StkBlueprintFunctionLibrary_eventStkGetMasterVolume_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkGetMasterVolume_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkGetMasterVolume_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkGetMasterVolume_Statics::Function_MetaDataParams[] = {
		{ "Category", "Volume" },
		{ "Comment", "/// Gets the master volume scale on the scene for all sound sources processed by SoundToolKit.\n/// Volume level is a value in range [0, 4].\n" },
		{ "ModuleRelativePath", "Public/StkBlueprintFunctionLibrary.h" },
		{ "ToolTip", "Gets the master volume scale on the scene for all sound sources processed by SoundToolKit.\nVolume level is a value in range [0, 4]." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkGetMasterVolume_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UStkBlueprintFunctionLibrary, nullptr, "StkGetMasterVolume", nullptr, nullptr, sizeof(StkBlueprintFunctionLibrary_eventStkGetMasterVolume_Parms), Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkGetMasterVolume_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkGetMasterVolume_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04042401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkGetMasterVolume_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkGetMasterVolume_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkGetMasterVolume()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkGetMasterVolume_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkGetReverbVolume_Statics
	{
		struct StkBlueprintFunctionLibrary_eventStkGetReverbVolume_Parms
		{
			float ReturnValue;
		};
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkGetReverbVolume_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(StkBlueprintFunctionLibrary_eventStkGetReverbVolume_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkGetReverbVolume_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkGetReverbVolume_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkGetReverbVolume_Statics::Function_MetaDataParams[] = {
		{ "Category", "Volume" },
		{ "Comment", "/// Gets the reverb volume scale on the scene for all sound sources processed by SoundToolKit.\n/// Volume level is a value in range [0, 4].\n" },
		{ "ModuleRelativePath", "Public/StkBlueprintFunctionLibrary.h" },
		{ "ToolTip", "Gets the reverb volume scale on the scene for all sound sources processed by SoundToolKit.\nVolume level is a value in range [0, 4]." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkGetReverbVolume_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UStkBlueprintFunctionLibrary, nullptr, "StkGetReverbVolume", nullptr, nullptr, sizeof(StkBlueprintFunctionLibrary_eventStkGetReverbVolume_Parms), Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkGetReverbVolume_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkGetReverbVolume_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04042401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkGetReverbVolume_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkGetReverbVolume_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkGetReverbVolume()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkGetReverbVolume_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkGetSpatialVolume_Statics
	{
		struct StkBlueprintFunctionLibrary_eventStkGetSpatialVolume_Parms
		{
			float ReturnValue;
		};
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkGetSpatialVolume_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(StkBlueprintFunctionLibrary_eventStkGetSpatialVolume_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkGetSpatialVolume_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkGetSpatialVolume_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkGetSpatialVolume_Statics::Function_MetaDataParams[] = {
		{ "Category", "Volume" },
		{ "Comment", "/// Gets the spatial volume scale on the scene for all sound sources processed by SoundToolKit.\n/// Volume level is a value in range [0, 4].\n" },
		{ "ModuleRelativePath", "Public/StkBlueprintFunctionLibrary.h" },
		{ "ToolTip", "Gets the spatial volume scale on the scene for all sound sources processed by SoundToolKit.\nVolume level is a value in range [0, 4]." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkGetSpatialVolume_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UStkBlueprintFunctionLibrary, nullptr, "StkGetSpatialVolume", nullptr, nullptr, sizeof(StkBlueprintFunctionLibrary_eventStkGetSpatialVolume_Parms), Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkGetSpatialVolume_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkGetSpatialVolume_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04042401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkGetSpatialVolume_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkGetSpatialVolume_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkGetSpatialVolume()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkGetSpatialVolume_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkGetSpeedOfSound_Statics
	{
		struct StkBlueprintFunctionLibrary_eventStkGetSpeedOfSound_Parms
		{
			float ReturnValue;
		};
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkGetSpeedOfSound_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(StkBlueprintFunctionLibrary_eventStkGetSpeedOfSound_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkGetSpeedOfSound_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkGetSpeedOfSound_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkGetSpeedOfSound_Statics::Function_MetaDataParams[] = {
		{ "Category", "Acoustic Medium" },
		{ "Comment", "/// Gets the speed of sound in a given acoustic medium [m/s] on the scene for all sound sources processed by SoundToolKit.\n/// Speed of sound value is a value in range [100, 1000].\n" },
		{ "ModuleRelativePath", "Public/StkBlueprintFunctionLibrary.h" },
		{ "ToolTip", "Gets the speed of sound in a given acoustic medium [m/s] on the scene for all sound sources processed by SoundToolKit.\nSpeed of sound value is a value in range [100, 1000]." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkGetSpeedOfSound_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UStkBlueprintFunctionLibrary, nullptr, "StkGetSpeedOfSound", nullptr, nullptr, sizeof(StkBlueprintFunctionLibrary_eventStkGetSpeedOfSound_Parms), Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkGetSpeedOfSound_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkGetSpeedOfSound_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04042401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkGetSpeedOfSound_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkGetSpeedOfSound_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkGetSpeedOfSound()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkGetSpeedOfSound_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsAttenuationEnabled_Statics
	{
		struct StkBlueprintFunctionLibrary_eventStkIsAttenuationEnabled_Parms
		{
			bool ReturnValue;
		};
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	void Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsAttenuationEnabled_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((StkBlueprintFunctionLibrary_eventStkIsAttenuationEnabled_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsAttenuationEnabled_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(StkBlueprintFunctionLibrary_eventStkIsAttenuationEnabled_Parms), &Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsAttenuationEnabled_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsAttenuationEnabled_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsAttenuationEnabled_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsAttenuationEnabled_Statics::Function_MetaDataParams[] = {
		{ "Category", "Spatial Effects" },
		{ "Comment", "/// Checks if global attenuation of sound with distance is enabled on the scene for all sound sources processed by SoundToolKit.\n" },
		{ "ModuleRelativePath", "Public/StkBlueprintFunctionLibrary.h" },
		{ "ToolTip", "Checks if global attenuation of sound with distance is enabled on the scene for all sound sources processed by SoundToolKit." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsAttenuationEnabled_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UStkBlueprintFunctionLibrary, nullptr, "StkIsAttenuationEnabled", nullptr, nullptr, sizeof(StkBlueprintFunctionLibrary_eventStkIsAttenuationEnabled_Parms), Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsAttenuationEnabled_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsAttenuationEnabled_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04042401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsAttenuationEnabled_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsAttenuationEnabled_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsAttenuationEnabled()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsAttenuationEnabled_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsDampingEnabled_Statics
	{
		struct StkBlueprintFunctionLibrary_eventStkIsDampingEnabled_Parms
		{
			bool ReturnValue;
		};
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	void Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsDampingEnabled_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((StkBlueprintFunctionLibrary_eventStkIsDampingEnabled_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsDampingEnabled_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(StkBlueprintFunctionLibrary_eventStkIsDampingEnabled_Parms), &Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsDampingEnabled_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsDampingEnabled_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsDampingEnabled_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsDampingEnabled_Statics::Function_MetaDataParams[] = {
		{ "Category", "Acoustic Medium" },
		{ "Comment", "/// Checks if attenuation due to acoustic medium viscosity is enabled on the scene for all sound sources processed by SoundToolKit.\n" },
		{ "ModuleRelativePath", "Public/StkBlueprintFunctionLibrary.h" },
		{ "ToolTip", "Checks if attenuation due to acoustic medium viscosity is enabled on the scene for all sound sources processed by SoundToolKit." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsDampingEnabled_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UStkBlueprintFunctionLibrary, nullptr, "StkIsDampingEnabled", nullptr, nullptr, sizeof(StkBlueprintFunctionLibrary_eventStkIsDampingEnabled_Parms), Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsDampingEnabled_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsDampingEnabled_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04042401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsDampingEnabled_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsDampingEnabled_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsDampingEnabled()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsDampingEnabled_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsDiffractionEnabled_Statics
	{
		struct StkBlueprintFunctionLibrary_eventStkIsDiffractionEnabled_Parms
		{
			bool ReturnValue;
		};
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	void Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsDiffractionEnabled_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((StkBlueprintFunctionLibrary_eventStkIsDiffractionEnabled_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsDiffractionEnabled_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(StkBlueprintFunctionLibrary_eventStkIsDiffractionEnabled_Parms), &Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsDiffractionEnabled_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsDiffractionEnabled_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsDiffractionEnabled_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsDiffractionEnabled_Statics::Function_MetaDataParams[] = {
		{ "Category", "Occlusion Effects" },
		{ "Comment", "/// Checks if global diffraction of sound on edges is enabled on the scene for all sound sources processed by SoundToolKit.\n" },
		{ "ModuleRelativePath", "Public/StkBlueprintFunctionLibrary.h" },
		{ "ToolTip", "Checks if global diffraction of sound on edges is enabled on the scene for all sound sources processed by SoundToolKit." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsDiffractionEnabled_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UStkBlueprintFunctionLibrary, nullptr, "StkIsDiffractionEnabled", nullptr, nullptr, sizeof(StkBlueprintFunctionLibrary_eventStkIsDiffractionEnabled_Parms), Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsDiffractionEnabled_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsDiffractionEnabled_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04042401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsDiffractionEnabled_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsDiffractionEnabled_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsDiffractionEnabled()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsDiffractionEnabled_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsHrtfEnabled_Statics
	{
		struct StkBlueprintFunctionLibrary_eventStkIsHrtfEnabled_Parms
		{
			bool ReturnValue;
		};
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	void Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsHrtfEnabled_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((StkBlueprintFunctionLibrary_eventStkIsHrtfEnabled_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsHrtfEnabled_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(StkBlueprintFunctionLibrary_eventStkIsHrtfEnabled_Parms), &Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsHrtfEnabled_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsHrtfEnabled_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsHrtfEnabled_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsHrtfEnabled_Statics::Function_MetaDataParams[] = {
		{ "Category", "Spatial Effects" },
		{ "Comment", "/// Checks if global HRTF spatialization is enabled on the scene for all sound sources processed by SoundToolKit.\n" },
		{ "ModuleRelativePath", "Public/StkBlueprintFunctionLibrary.h" },
		{ "ToolTip", "Checks if global HRTF spatialization is enabled on the scene for all sound sources processed by SoundToolKit." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsHrtfEnabled_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UStkBlueprintFunctionLibrary, nullptr, "StkIsHrtfEnabled", nullptr, nullptr, sizeof(StkBlueprintFunctionLibrary_eventStkIsHrtfEnabled_Parms), Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsHrtfEnabled_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsHrtfEnabled_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04042401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsHrtfEnabled_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsHrtfEnabled_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsHrtfEnabled()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsHrtfEnabled_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsReflectionEnabled_Statics
	{
		struct StkBlueprintFunctionLibrary_eventStkIsReflectionEnabled_Parms
		{
			bool ReturnValue;
		};
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	void Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsReflectionEnabled_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((StkBlueprintFunctionLibrary_eventStkIsReflectionEnabled_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsReflectionEnabled_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(StkBlueprintFunctionLibrary_eventStkIsReflectionEnabled_Parms), &Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsReflectionEnabled_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsReflectionEnabled_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsReflectionEnabled_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsReflectionEnabled_Statics::Function_MetaDataParams[] = {
		{ "Category", "Occlusion Effects" },
		{ "Comment", "/// Checks if global specular reflection of sound from obstacles is enabled on the scene for all sound sources processed by SoundToolKit.\n" },
		{ "ModuleRelativePath", "Public/StkBlueprintFunctionLibrary.h" },
		{ "ToolTip", "Checks if global specular reflection of sound from obstacles is enabled on the scene for all sound sources processed by SoundToolKit." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsReflectionEnabled_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UStkBlueprintFunctionLibrary, nullptr, "StkIsReflectionEnabled", nullptr, nullptr, sizeof(StkBlueprintFunctionLibrary_eventStkIsReflectionEnabled_Parms), Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsReflectionEnabled_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsReflectionEnabled_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04042401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsReflectionEnabled_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsReflectionEnabled_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsReflectionEnabled()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsReflectionEnabled_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsTransmissionEnabled_Statics
	{
		struct StkBlueprintFunctionLibrary_eventStkIsTransmissionEnabled_Parms
		{
			bool ReturnValue;
		};
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	void Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsTransmissionEnabled_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((StkBlueprintFunctionLibrary_eventStkIsTransmissionEnabled_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsTransmissionEnabled_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(StkBlueprintFunctionLibrary_eventStkIsTransmissionEnabled_Parms), &Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsTransmissionEnabled_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsTransmissionEnabled_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsTransmissionEnabled_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsTransmissionEnabled_Statics::Function_MetaDataParams[] = {
		{ "Category", "Occlusion Effects" },
		{ "Comment", "/// Checks if global transmission of sound through obstacles is enabled on the scene for all sound sources processed by SoundToolKit.\n" },
		{ "ModuleRelativePath", "Public/StkBlueprintFunctionLibrary.h" },
		{ "ToolTip", "Checks if global transmission of sound through obstacles is enabled on the scene for all sound sources processed by SoundToolKit." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsTransmissionEnabled_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UStkBlueprintFunctionLibrary, nullptr, "StkIsTransmissionEnabled", nullptr, nullptr, sizeof(StkBlueprintFunctionLibrary_eventStkIsTransmissionEnabled_Parms), Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsTransmissionEnabled_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsTransmissionEnabled_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04042401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsTransmissionEnabled_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsTransmissionEnabled_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsTransmissionEnabled()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsTransmissionEnabled_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkSetDampingCoefficients_Statics
	{
		struct StkBlueprintFunctionLibrary_eventStkSetDampingCoefficients_Parms
		{
			FStkEffectCoefficients DampingCoefficients;
		};
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_DampingCoefficients;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkSetDampingCoefficients_Statics::NewProp_DampingCoefficients = { "DampingCoefficients", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(StkBlueprintFunctionLibrary_eventStkSetDampingCoefficients_Parms, DampingCoefficients), Z_Construct_UScriptStruct_FStkEffectCoefficients, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkSetDampingCoefficients_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkSetDampingCoefficients_Statics::NewProp_DampingCoefficients,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkSetDampingCoefficients_Statics::Function_MetaDataParams[] = {
		{ "Category", "Acoustic Medium" },
		{ "Comment", "/// Sets the coefficients for attenuation due to medium viscosity on the scene for all sound sources processed by SoundToolKit.\n/// Coefficient value for every band should be in range [0, 1], other values are clamped.\n" },
		{ "ModuleRelativePath", "Public/StkBlueprintFunctionLibrary.h" },
		{ "ToolTip", "Sets the coefficients for attenuation due to medium viscosity on the scene for all sound sources processed by SoundToolKit.\nCoefficient value for every band should be in range [0, 1], other values are clamped." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkSetDampingCoefficients_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UStkBlueprintFunctionLibrary, nullptr, "StkSetDampingCoefficients", nullptr, nullptr, sizeof(StkBlueprintFunctionLibrary_eventStkSetDampingCoefficients_Parms), Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkSetDampingCoefficients_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkSetDampingCoefficients_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04042401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkSetDampingCoefficients_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkSetDampingCoefficients_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkSetDampingCoefficients()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkSetDampingCoefficients_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkSetMasterVolume_Statics
	{
		struct StkBlueprintFunctionLibrary_eventStkSetMasterVolume_Parms
		{
			float Volume;
		};
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_Volume;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkSetMasterVolume_Statics::NewProp_Volume = { "Volume", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(StkBlueprintFunctionLibrary_eventStkSetMasterVolume_Parms, Volume), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkSetMasterVolume_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkSetMasterVolume_Statics::NewProp_Volume,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkSetMasterVolume_Statics::Function_MetaDataParams[] = {
		{ "Category", "Volume" },
		{ "Comment", "/// Sets the master volume scale on the scene for all sound sources processed by SoundToolKit.\n/// Volume level should be in range [0, 4], other values are clamped.\n" },
		{ "ModuleRelativePath", "Public/StkBlueprintFunctionLibrary.h" },
		{ "ToolTip", "Sets the master volume scale on the scene for all sound sources processed by SoundToolKit.\nVolume level should be in range [0, 4], other values are clamped." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkSetMasterVolume_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UStkBlueprintFunctionLibrary, nullptr, "StkSetMasterVolume", nullptr, nullptr, sizeof(StkBlueprintFunctionLibrary_eventStkSetMasterVolume_Parms), Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkSetMasterVolume_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkSetMasterVolume_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04042401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkSetMasterVolume_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkSetMasterVolume_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkSetMasterVolume()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkSetMasterVolume_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkSetReverbVolume_Statics
	{
		struct StkBlueprintFunctionLibrary_eventStkSetReverbVolume_Parms
		{
			float Volume;
		};
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_Volume;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkSetReverbVolume_Statics::NewProp_Volume = { "Volume", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(StkBlueprintFunctionLibrary_eventStkSetReverbVolume_Parms, Volume), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkSetReverbVolume_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkSetReverbVolume_Statics::NewProp_Volume,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkSetReverbVolume_Statics::Function_MetaDataParams[] = {
		{ "Category", "Volume" },
		{ "Comment", "/// Sets the reverb volume scale on the scene for all sound sources processed by SoundToolKit.\n/// Volume level should be in range [0, 4], other values are clamped.\n" },
		{ "ModuleRelativePath", "Public/StkBlueprintFunctionLibrary.h" },
		{ "ToolTip", "Sets the reverb volume scale on the scene for all sound sources processed by SoundToolKit.\nVolume level should be in range [0, 4], other values are clamped." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkSetReverbVolume_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UStkBlueprintFunctionLibrary, nullptr, "StkSetReverbVolume", nullptr, nullptr, sizeof(StkBlueprintFunctionLibrary_eventStkSetReverbVolume_Parms), Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkSetReverbVolume_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkSetReverbVolume_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04042401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkSetReverbVolume_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkSetReverbVolume_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkSetReverbVolume()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkSetReverbVolume_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkSetSpatialVolume_Statics
	{
		struct StkBlueprintFunctionLibrary_eventStkSetSpatialVolume_Parms
		{
			float Volume;
		};
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_Volume;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkSetSpatialVolume_Statics::NewProp_Volume = { "Volume", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(StkBlueprintFunctionLibrary_eventStkSetSpatialVolume_Parms, Volume), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkSetSpatialVolume_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkSetSpatialVolume_Statics::NewProp_Volume,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkSetSpatialVolume_Statics::Function_MetaDataParams[] = {
		{ "Category", "Volume" },
		{ "Comment", "/// Sets the spatial volume scale on the scene for all sound sources processed by SoundToolKit.\n/// Volume level should be in range [0, 4], other values are clamped.\n" },
		{ "ModuleRelativePath", "Public/StkBlueprintFunctionLibrary.h" },
		{ "ToolTip", "Sets the spatial volume scale on the scene for all sound sources processed by SoundToolKit.\nVolume level should be in range [0, 4], other values are clamped." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkSetSpatialVolume_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UStkBlueprintFunctionLibrary, nullptr, "StkSetSpatialVolume", nullptr, nullptr, sizeof(StkBlueprintFunctionLibrary_eventStkSetSpatialVolume_Parms), Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkSetSpatialVolume_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkSetSpatialVolume_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04042401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkSetSpatialVolume_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkSetSpatialVolume_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkSetSpatialVolume()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkSetSpatialVolume_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkSetSpeedOfSound_Statics
	{
		struct StkBlueprintFunctionLibrary_eventStkSetSpeedOfSound_Parms
		{
			float SpeedOfSound;
		};
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_SpeedOfSound;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkSetSpeedOfSound_Statics::NewProp_SpeedOfSound = { "SpeedOfSound", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(StkBlueprintFunctionLibrary_eventStkSetSpeedOfSound_Parms, SpeedOfSound), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkSetSpeedOfSound_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkSetSpeedOfSound_Statics::NewProp_SpeedOfSound,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkSetSpeedOfSound_Statics::Function_MetaDataParams[] = {
		{ "Category", "Acoustic Medium" },
		{ "Comment", "/// Sets the speed of sound in a given acoustic medium [m/s] on the scene for all sound sources processed by SoundToolKit.\n/// Speed of sound value should be in range [100, 1000], other values are clamped.\n" },
		{ "ModuleRelativePath", "Public/StkBlueprintFunctionLibrary.h" },
		{ "ToolTip", "Sets the speed of sound in a given acoustic medium [m/s] on the scene for all sound sources processed by SoundToolKit.\nSpeed of sound value should be in range [100, 1000], other values are clamped." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkSetSpeedOfSound_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UStkBlueprintFunctionLibrary, nullptr, "StkSetSpeedOfSound", nullptr, nullptr, sizeof(StkBlueprintFunctionLibrary_eventStkSetSpeedOfSound_Parms), Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkSetSpeedOfSound_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkSetSpeedOfSound_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04042401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkSetSpeedOfSound_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkSetSpeedOfSound_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkSetSpeedOfSound()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkSetSpeedOfSound_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UStkBlueprintFunctionLibrary_NoRegister()
	{
		return UStkBlueprintFunctionLibrary::StaticClass();
	}
	struct Z_Construct_UClass_UStkBlueprintFunctionLibrary_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UStkBlueprintFunctionLibrary_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UBlueprintFunctionLibrary,
		(UObject* (*)())Z_Construct_UPackage__Script_StkGameModule,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UStkBlueprintFunctionLibrary_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkDisableAttenuation, "StkDisableAttenuation" }, // 1726737909
		{ &Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkDisableDamping, "StkDisableDamping" }, // 314729502
		{ &Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkDisableDiffraction, "StkDisableDiffraction" }, // 3478136641
		{ &Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkDisableHrtf, "StkDisableHrtf" }, // 3950743929
		{ &Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkDisableReflection, "StkDisableReflection" }, // 2995829979
		{ &Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkDisableTransmission, "StkDisableTransmission" }, // 384493205
		{ &Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkEnableAttenuation, "StkEnableAttenuation" }, // 34924640
		{ &Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkEnableDamping, "StkEnableDamping" }, // 771474872
		{ &Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkEnableDiffraction, "StkEnableDiffraction" }, // 615399540
		{ &Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkEnableHrtf, "StkEnableHrtf" }, // 3312769550
		{ &Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkEnableReflection, "StkEnableReflection" }, // 893157510
		{ &Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkEnableTransmission, "StkEnableTransmission" }, // 2704717987
		{ &Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkGetDampingCoefficients, "StkGetDampingCoefficients" }, // 1906230616
		{ &Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkGetMasterVolume, "StkGetMasterVolume" }, // 1652187178
		{ &Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkGetReverbVolume, "StkGetReverbVolume" }, // 1616119516
		{ &Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkGetSpatialVolume, "StkGetSpatialVolume" }, // 1087154079
		{ &Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkGetSpeedOfSound, "StkGetSpeedOfSound" }, // 2572023336
		{ &Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsAttenuationEnabled, "StkIsAttenuationEnabled" }, // 2901734397
		{ &Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsDampingEnabled, "StkIsDampingEnabled" }, // 3947966655
		{ &Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsDiffractionEnabled, "StkIsDiffractionEnabled" }, // 2566087122
		{ &Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsHrtfEnabled, "StkIsHrtfEnabled" }, // 3628220677
		{ &Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsReflectionEnabled, "StkIsReflectionEnabled" }, // 754083463
		{ &Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkIsTransmissionEnabled, "StkIsTransmissionEnabled" }, // 2475424527
		{ &Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkSetDampingCoefficients, "StkSetDampingCoefficients" }, // 250302179
		{ &Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkSetMasterVolume, "StkSetMasterVolume" }, // 1042999006
		{ &Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkSetReverbVolume, "StkSetReverbVolume" }, // 488364434
		{ &Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkSetSpatialVolume, "StkSetSpatialVolume" }, // 1195156225
		{ &Z_Construct_UFunction_UStkBlueprintFunctionLibrary_StkSetSpeedOfSound, "StkSetSpeedOfSound" }, // 2378765014
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UStkBlueprintFunctionLibrary_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "StkBlueprintFunctionLibrary.h" },
		{ "ModuleRelativePath", "Public/StkBlueprintFunctionLibrary.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UStkBlueprintFunctionLibrary_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UStkBlueprintFunctionLibrary>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UStkBlueprintFunctionLibrary_Statics::ClassParams = {
		&UStkBlueprintFunctionLibrary::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		0,
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UStkBlueprintFunctionLibrary_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UStkBlueprintFunctionLibrary_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UStkBlueprintFunctionLibrary()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UStkBlueprintFunctionLibrary_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UStkBlueprintFunctionLibrary, 1668649697);
	template<> STKGAMEMODULE_API UClass* StaticClass<UStkBlueprintFunctionLibrary>()
	{
		return UStkBlueprintFunctionLibrary::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UStkBlueprintFunctionLibrary(Z_Construct_UClass_UStkBlueprintFunctionLibrary, &UStkBlueprintFunctionLibrary::StaticClass, TEXT("/Script/StkGameModule"), TEXT("UStkBlueprintFunctionLibrary"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UStkBlueprintFunctionLibrary);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
