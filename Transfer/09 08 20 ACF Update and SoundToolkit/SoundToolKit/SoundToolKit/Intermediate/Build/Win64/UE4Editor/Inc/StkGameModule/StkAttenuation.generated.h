// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef STKGAMEMODULE_StkAttenuation_generated_h
#error "StkAttenuation.generated.h already included, missing '#pragma once' in StkAttenuation.h"
#endif
#define STKGAMEMODULE_StkAttenuation_generated_h

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID HostProject_Plugins_SoundToolKit_Source_StkGameModule_Public_StkAttenuation_h


#define FOREACH_ENUM_ESTKATTENUATIONFUNCTION(op) \
	op(EStkAttenuationFunction::StkAttenuation_Nothing) \
	op(EStkAttenuationFunction::StkAttenuation_Linear) \
	op(EStkAttenuationFunction::StkAttenuation_Inverse) \
	op(EStkAttenuationFunction::StkAttenuation_Logarithmic) \
	op(EStkAttenuationFunction::StkAttenuation_LineSource) \
	op(EStkAttenuationFunction::StkAttenuation_PointSource) \
	op(EStkAttenuationFunction::StkAttenuation_ReverseLog) \
	op(EStkAttenuationFunction::StkAttenuation_Custom) 

enum class EStkAttenuationFunction : uint8;
template<> STKGAMEMODULE_API UEnum* StaticEnum<EStkAttenuationFunction>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
