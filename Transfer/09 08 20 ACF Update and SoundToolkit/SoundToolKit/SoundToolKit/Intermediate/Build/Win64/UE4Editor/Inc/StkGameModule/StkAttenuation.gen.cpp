// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "StkGameModule/Public/StkAttenuation.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeStkAttenuation() {}
// Cross Module References
	STKGAMEMODULE_API UEnum* Z_Construct_UEnum_StkGameModule_EStkAttenuationFunction();
	UPackage* Z_Construct_UPackage__Script_StkGameModule();
// End Cross Module References
	static UEnum* EStkAttenuationFunction_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_StkGameModule_EStkAttenuationFunction, Z_Construct_UPackage__Script_StkGameModule(), TEXT("EStkAttenuationFunction"));
		}
		return Singleton;
	}
	template<> STKGAMEMODULE_API UEnum* StaticEnum<EStkAttenuationFunction>()
	{
		return EStkAttenuationFunction_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_EStkAttenuationFunction(EStkAttenuationFunction_StaticEnum, TEXT("/Script/StkGameModule"), TEXT("EStkAttenuationFunction"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_StkGameModule_EStkAttenuationFunction_Hash() { return 1450686988U; }
	UEnum* Z_Construct_UEnum_StkGameModule_EStkAttenuationFunction()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_StkGameModule();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("EStkAttenuationFunction"), 0, Get_Z_Construct_UEnum_StkGameModule_EStkAttenuationFunction_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "EStkAttenuationFunction::StkAttenuation_Nothing", (int64)EStkAttenuationFunction::StkAttenuation_Nothing },
				{ "EStkAttenuationFunction::StkAttenuation_Linear", (int64)EStkAttenuationFunction::StkAttenuation_Linear },
				{ "EStkAttenuationFunction::StkAttenuation_Inverse", (int64)EStkAttenuationFunction::StkAttenuation_Inverse },
				{ "EStkAttenuationFunction::StkAttenuation_Logarithmic", (int64)EStkAttenuationFunction::StkAttenuation_Logarithmic },
				{ "EStkAttenuationFunction::StkAttenuation_LineSource", (int64)EStkAttenuationFunction::StkAttenuation_LineSource },
				{ "EStkAttenuationFunction::StkAttenuation_PointSource", (int64)EStkAttenuationFunction::StkAttenuation_PointSource },
				{ "EStkAttenuationFunction::StkAttenuation_ReverseLog", (int64)EStkAttenuationFunction::StkAttenuation_ReverseLog },
				{ "EStkAttenuationFunction::StkAttenuation_Custom", (int64)EStkAttenuationFunction::StkAttenuation_Custom },
			};
#if WITH_METADATA
			const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "ModuleRelativePath", "Public/StkAttenuation.h" },
				{ "StkAttenuation_Custom.DisplayName", "Custom" },
				{ "StkAttenuation_Custom.Name", "EStkAttenuationFunction::StkAttenuation_Custom" },
				{ "StkAttenuation_Inverse.DisplayName", "Inverse" },
				{ "StkAttenuation_Inverse.Name", "EStkAttenuationFunction::StkAttenuation_Inverse" },
				{ "StkAttenuation_Linear.DisplayName", "Linear" },
				{ "StkAttenuation_Linear.Name", "EStkAttenuationFunction::StkAttenuation_Linear" },
				{ "StkAttenuation_LineSource.DisplayName", "Line Source" },
				{ "StkAttenuation_LineSource.Name", "EStkAttenuationFunction::StkAttenuation_LineSource" },
				{ "StkAttenuation_Logarithmic.DisplayName", "Logarithmic" },
				{ "StkAttenuation_Logarithmic.Name", "EStkAttenuationFunction::StkAttenuation_Logarithmic" },
				{ "StkAttenuation_Nothing.DisplayName", "Nothing" },
				{ "StkAttenuation_Nothing.Name", "EStkAttenuationFunction::StkAttenuation_Nothing" },
				{ "StkAttenuation_PointSource.DisplayName", "Point Source" },
				{ "StkAttenuation_PointSource.Name", "EStkAttenuationFunction::StkAttenuation_PointSource" },
				{ "StkAttenuation_ReverseLog.DisplayName", "Reverse Logarithm" },
				{ "StkAttenuation_ReverseLog.Name", "EStkAttenuationFunction::StkAttenuation_ReverseLog" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_StkGameModule,
				nullptr,
				"EStkAttenuationFunction",
				"EStkAttenuationFunction",
				Enumerators,
				UE_ARRAY_COUNT(Enumerators),
				RF_Public|RF_Transient|RF_MarkAsNative,
				UE4CodeGen_Private::EDynamicType::NotDynamic,
				(uint8)UEnum::ECppForm::EnumClass,
				METADATA_PARAMS(Enum_MetaDataParams, UE_ARRAY_COUNT(Enum_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams);
		}
		return ReturnEnum;
	}
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
