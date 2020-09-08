// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "StkGameModule/Private/StkEffectCoefficients.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeStkEffectCoefficients() {}
// Cross Module References
	STKGAMEMODULE_API UScriptStruct* Z_Construct_UScriptStruct_FStkEffectCoefficients();
	UPackage* Z_Construct_UPackage__Script_StkGameModule();
// End Cross Module References
class UScriptStruct* FStkEffectCoefficients::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern STKGAMEMODULE_API uint32 Get_Z_Construct_UScriptStruct_FStkEffectCoefficients_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FStkEffectCoefficients, Z_Construct_UPackage__Script_StkGameModule(), TEXT("StkEffectCoefficients"), sizeof(FStkEffectCoefficients), Get_Z_Construct_UScriptStruct_FStkEffectCoefficients_Hash());
	}
	return Singleton;
}
template<> STKGAMEMODULE_API UScriptStruct* StaticStruct<FStkEffectCoefficients>()
{
	return FStkEffectCoefficients::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FStkEffectCoefficients(FStkEffectCoefficients::StaticStruct, TEXT("/Script/StkGameModule"), TEXT("StkEffectCoefficients"), false, nullptr, nullptr);
static struct FScriptStruct_StkGameModule_StaticRegisterNativesFStkEffectCoefficients
{
	FScriptStruct_StkGameModule_StaticRegisterNativesFStkEffectCoefficients()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("StkEffectCoefficients")),new UScriptStruct::TCppStructOps<FStkEffectCoefficients>);
	}
} ScriptStruct_StkGameModule_StaticRegisterNativesFStkEffectCoefficients;
	struct Z_Construct_UScriptStruct_FStkEffectCoefficients_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Band16000Hz_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_Band16000Hz;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Band8000Hz_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_Band8000Hz;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Band4000Hz_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_Band4000Hz;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Band2000Hz_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_Band2000Hz;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Band1000Hz_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_Band1000Hz;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Band500Hz_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_Band500Hz;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Band250Hz_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_Band250Hz;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Band125Hz_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_Band125Hz;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FStkEffectCoefficients_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Private/StkEffectCoefficients.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FStkEffectCoefficients_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FStkEffectCoefficients>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FStkEffectCoefficients_Statics::NewProp_Band16000Hz_MetaData[] = {
		{ "Category", "Effect Severity" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
		{ "Comment", "/// Effect severity in a 16 kHz octave band.\n" },
		{ "DisplayName", "16000 Hz" },
		{ "ModuleRelativePath", "Private/StkEffectCoefficients.h" },
		{ "ToolTip", "Effect severity in a 16 kHz octave band." },
		{ "UIMax", "1.0" },
		{ "UIMin", "0.0" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FStkEffectCoefficients_Statics::NewProp_Band16000Hz = { "Band16000Hz", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FStkEffectCoefficients, Band16000Hz), METADATA_PARAMS(Z_Construct_UScriptStruct_FStkEffectCoefficients_Statics::NewProp_Band16000Hz_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FStkEffectCoefficients_Statics::NewProp_Band16000Hz_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FStkEffectCoefficients_Statics::NewProp_Band8000Hz_MetaData[] = {
		{ "Category", "Effect Severity" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
		{ "Comment", "/// Effect severity in a 8 kHz octave band.\n" },
		{ "DisplayName", "8000 Hz" },
		{ "ModuleRelativePath", "Private/StkEffectCoefficients.h" },
		{ "ToolTip", "Effect severity in a 8 kHz octave band." },
		{ "UIMax", "1.0" },
		{ "UIMin", "0.0" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FStkEffectCoefficients_Statics::NewProp_Band8000Hz = { "Band8000Hz", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FStkEffectCoefficients, Band8000Hz), METADATA_PARAMS(Z_Construct_UScriptStruct_FStkEffectCoefficients_Statics::NewProp_Band8000Hz_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FStkEffectCoefficients_Statics::NewProp_Band8000Hz_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FStkEffectCoefficients_Statics::NewProp_Band4000Hz_MetaData[] = {
		{ "Category", "Effect Severity" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
		{ "Comment", "/// Effect severity in a 4 kHz octave band.\n" },
		{ "DisplayName", "4000 Hz" },
		{ "ModuleRelativePath", "Private/StkEffectCoefficients.h" },
		{ "ToolTip", "Effect severity in a 4 kHz octave band." },
		{ "UIMax", "1.0" },
		{ "UIMin", "0.0" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FStkEffectCoefficients_Statics::NewProp_Band4000Hz = { "Band4000Hz", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FStkEffectCoefficients, Band4000Hz), METADATA_PARAMS(Z_Construct_UScriptStruct_FStkEffectCoefficients_Statics::NewProp_Band4000Hz_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FStkEffectCoefficients_Statics::NewProp_Band4000Hz_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FStkEffectCoefficients_Statics::NewProp_Band2000Hz_MetaData[] = {
		{ "Category", "Effect Severity" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
		{ "Comment", "/// Effect severity in a 2 kHz octave band.\n" },
		{ "DisplayName", "2000 Hz" },
		{ "ModuleRelativePath", "Private/StkEffectCoefficients.h" },
		{ "ToolTip", "Effect severity in a 2 kHz octave band." },
		{ "UIMax", "1.0" },
		{ "UIMin", "0.0" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FStkEffectCoefficients_Statics::NewProp_Band2000Hz = { "Band2000Hz", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FStkEffectCoefficients, Band2000Hz), METADATA_PARAMS(Z_Construct_UScriptStruct_FStkEffectCoefficients_Statics::NewProp_Band2000Hz_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FStkEffectCoefficients_Statics::NewProp_Band2000Hz_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FStkEffectCoefficients_Statics::NewProp_Band1000Hz_MetaData[] = {
		{ "Category", "Effect Severity" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
		{ "Comment", "/// Effect severity in a 1 kHz octave band.\n" },
		{ "DisplayName", "1000 Hz" },
		{ "ModuleRelativePath", "Private/StkEffectCoefficients.h" },
		{ "ToolTip", "Effect severity in a 1 kHz octave band." },
		{ "UIMax", "1.0" },
		{ "UIMin", "0.0" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FStkEffectCoefficients_Statics::NewProp_Band1000Hz = { "Band1000Hz", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FStkEffectCoefficients, Band1000Hz), METADATA_PARAMS(Z_Construct_UScriptStruct_FStkEffectCoefficients_Statics::NewProp_Band1000Hz_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FStkEffectCoefficients_Statics::NewProp_Band1000Hz_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FStkEffectCoefficients_Statics::NewProp_Band500Hz_MetaData[] = {
		{ "Category", "Effect Severity" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
		{ "Comment", "/// Effect severity in a 500 Hz octave band.\n" },
		{ "DisplayName", "500 Hz" },
		{ "ModuleRelativePath", "Private/StkEffectCoefficients.h" },
		{ "ToolTip", "Effect severity in a 500 Hz octave band." },
		{ "UIMax", "1.0" },
		{ "UIMin", "0.0" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FStkEffectCoefficients_Statics::NewProp_Band500Hz = { "Band500Hz", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FStkEffectCoefficients, Band500Hz), METADATA_PARAMS(Z_Construct_UScriptStruct_FStkEffectCoefficients_Statics::NewProp_Band500Hz_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FStkEffectCoefficients_Statics::NewProp_Band500Hz_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FStkEffectCoefficients_Statics::NewProp_Band250Hz_MetaData[] = {
		{ "Category", "Effect Severity" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
		{ "Comment", "/// Effect severity in a 250 Hz octave band.\n" },
		{ "DisplayName", "250 Hz" },
		{ "ModuleRelativePath", "Private/StkEffectCoefficients.h" },
		{ "ToolTip", "Effect severity in a 250 Hz octave band." },
		{ "UIMax", "1.0" },
		{ "UIMin", "0.0" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FStkEffectCoefficients_Statics::NewProp_Band250Hz = { "Band250Hz", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FStkEffectCoefficients, Band250Hz), METADATA_PARAMS(Z_Construct_UScriptStruct_FStkEffectCoefficients_Statics::NewProp_Band250Hz_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FStkEffectCoefficients_Statics::NewProp_Band250Hz_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FStkEffectCoefficients_Statics::NewProp_Band125Hz_MetaData[] = {
		{ "Category", "Effect Severity" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
		{ "Comment", "/// Effect severity in a 125 Hz octave band.\n" },
		{ "DisplayName", "125 Hz" },
		{ "ModuleRelativePath", "Private/StkEffectCoefficients.h" },
		{ "ToolTip", "Effect severity in a 125 Hz octave band." },
		{ "UIMax", "1.0" },
		{ "UIMin", "0.0" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FStkEffectCoefficients_Statics::NewProp_Band125Hz = { "Band125Hz", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FStkEffectCoefficients, Band125Hz), METADATA_PARAMS(Z_Construct_UScriptStruct_FStkEffectCoefficients_Statics::NewProp_Band125Hz_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FStkEffectCoefficients_Statics::NewProp_Band125Hz_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FStkEffectCoefficients_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FStkEffectCoefficients_Statics::NewProp_Band16000Hz,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FStkEffectCoefficients_Statics::NewProp_Band8000Hz,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FStkEffectCoefficients_Statics::NewProp_Band4000Hz,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FStkEffectCoefficients_Statics::NewProp_Band2000Hz,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FStkEffectCoefficients_Statics::NewProp_Band1000Hz,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FStkEffectCoefficients_Statics::NewProp_Band500Hz,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FStkEffectCoefficients_Statics::NewProp_Band250Hz,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FStkEffectCoefficients_Statics::NewProp_Band125Hz,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FStkEffectCoefficients_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_StkGameModule,
		nullptr,
		&NewStructOps,
		"StkEffectCoefficients",
		sizeof(FStkEffectCoefficients),
		alignof(FStkEffectCoefficients),
		Z_Construct_UScriptStruct_FStkEffectCoefficients_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FStkEffectCoefficients_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FStkEffectCoefficients_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FStkEffectCoefficients_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FStkEffectCoefficients()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FStkEffectCoefficients_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_StkGameModule();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("StkEffectCoefficients"), sizeof(FStkEffectCoefficients), Get_Z_Construct_UScriptStruct_FStkEffectCoefficients_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FStkEffectCoefficients_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FStkEffectCoefficients_Hash() { return 298805532U; }
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
