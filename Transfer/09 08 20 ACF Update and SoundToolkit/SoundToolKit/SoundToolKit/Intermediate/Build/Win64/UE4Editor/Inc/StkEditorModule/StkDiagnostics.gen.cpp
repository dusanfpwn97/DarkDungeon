// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "StkEditorModule/Private/StkDiagnostics.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeStkDiagnostics() {}
// Cross Module References
	STKEDITORMODULE_API UScriptStruct* Z_Construct_UScriptStruct_FActiveSoundDiagnostic();
	UPackage* Z_Construct_UPackage__Script_StkEditorModule();
	STKEDITORMODULE_API UScriptStruct* Z_Construct_UScriptStruct_FStatusIndicator();
	STKEDITORMODULE_API UClass* Z_Construct_UClass_AStkDiagnostics_NoRegister();
	STKEDITORMODULE_API UClass* Z_Construct_UClass_AStkDiagnostics();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
// End Cross Module References
class UScriptStruct* FActiveSoundDiagnostic::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern STKEDITORMODULE_API uint32 Get_Z_Construct_UScriptStruct_FActiveSoundDiagnostic_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FActiveSoundDiagnostic, Z_Construct_UPackage__Script_StkEditorModule(), TEXT("ActiveSoundDiagnostic"), sizeof(FActiveSoundDiagnostic), Get_Z_Construct_UScriptStruct_FActiveSoundDiagnostic_Hash());
	}
	return Singleton;
}
template<> STKEDITORMODULE_API UScriptStruct* StaticStruct<FActiveSoundDiagnostic>()
{
	return FActiveSoundDiagnostic::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FActiveSoundDiagnostic(FActiveSoundDiagnostic::StaticStruct, TEXT("/Script/StkEditorModule"), TEXT("ActiveSoundDiagnostic"), false, nullptr, nullptr);
static struct FScriptStruct_StkEditorModule_StaticRegisterNativesFActiveSoundDiagnostic
{
	FScriptStruct_StkEditorModule_StaticRegisterNativesFActiveSoundDiagnostic()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("ActiveSoundDiagnostic")),new UScriptStruct::TCppStructOps<FActiveSoundDiagnostic>);
	}
} ScriptStruct_StkEditorModule_StaticRegisterNativesFActiveSoundDiagnostic;
	struct Z_Construct_UScriptStruct_FActiveSoundDiagnostic_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bProcessedByUnrealEngine_MetaData[];
#endif
		static void NewProp_bProcessedByUnrealEngine_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bProcessedByUnrealEngine;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bProcessedBySoundToolKit_MetaData[];
#endif
		static void NewProp_bProcessedBySoundToolKit_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bProcessedBySoundToolKit;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bSpatializationEnabled_MetaData[];
#endif
		static void NewProp_bSpatializationEnabled_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bSpatializationEnabled;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Position_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Position;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Sample_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Sample;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Actor_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Actor;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FActiveSoundDiagnostic_Statics::Struct_MetaDataParams[] = {
		{ "Comment", "/// <summary>\n/// Struct used respresent hold sound source diagnostic data.\n/// </summary>\n" },
		{ "ModuleRelativePath", "Private/StkDiagnostics.h" },
		{ "ToolTip", "<summary>\nStruct used respresent hold sound source diagnostic data.\n</summary>" },
	};
#endif
	void* Z_Construct_UScriptStruct_FActiveSoundDiagnostic_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FActiveSoundDiagnostic>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FActiveSoundDiagnostic_Statics::NewProp_bProcessedByUnrealEngine_MetaData[] = {
		{ "Category", "Active Sound" },
		{ "Comment", "/// Is this sound source currently processed by Unreal sound engine \n" },
		{ "ModuleRelativePath", "Private/StkDiagnostics.h" },
		{ "ToolTip", "Is this sound source currently processed by Unreal sound engine" },
	};
#endif
	void Z_Construct_UScriptStruct_FActiveSoundDiagnostic_Statics::NewProp_bProcessedByUnrealEngine_SetBit(void* Obj)
	{
		((FActiveSoundDiagnostic*)Obj)->bProcessedByUnrealEngine = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FActiveSoundDiagnostic_Statics::NewProp_bProcessedByUnrealEngine = { "bProcessedByUnrealEngine", nullptr, (EPropertyFlags)0x0010000000020001, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FActiveSoundDiagnostic), &Z_Construct_UScriptStruct_FActiveSoundDiagnostic_Statics::NewProp_bProcessedByUnrealEngine_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FActiveSoundDiagnostic_Statics::NewProp_bProcessedByUnrealEngine_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FActiveSoundDiagnostic_Statics::NewProp_bProcessedByUnrealEngine_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FActiveSoundDiagnostic_Statics::NewProp_bProcessedBySoundToolKit_MetaData[] = {
		{ "Category", "Active Sound" },
		{ "Comment", "/// Is this sound source currently processed by STK\n" },
		{ "ModuleRelativePath", "Private/StkDiagnostics.h" },
		{ "ToolTip", "Is this sound source currently processed by STK" },
	};
#endif
	void Z_Construct_UScriptStruct_FActiveSoundDiagnostic_Statics::NewProp_bProcessedBySoundToolKit_SetBit(void* Obj)
	{
		((FActiveSoundDiagnostic*)Obj)->bProcessedBySoundToolKit = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FActiveSoundDiagnostic_Statics::NewProp_bProcessedBySoundToolKit = { "bProcessedBySoundToolKit", nullptr, (EPropertyFlags)0x0010000000020001, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FActiveSoundDiagnostic), &Z_Construct_UScriptStruct_FActiveSoundDiagnostic_Statics::NewProp_bProcessedBySoundToolKit_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FActiveSoundDiagnostic_Statics::NewProp_bProcessedBySoundToolKit_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FActiveSoundDiagnostic_Statics::NewProp_bProcessedBySoundToolKit_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FActiveSoundDiagnostic_Statics::NewProp_bSpatializationEnabled_MetaData[] = {
		{ "Category", "Active Sound" },
		{ "Comment", "/// Is sound spatialization enabled for this sound source\n" },
		{ "ModuleRelativePath", "Private/StkDiagnostics.h" },
		{ "ToolTip", "Is sound spatialization enabled for this sound source" },
	};
#endif
	void Z_Construct_UScriptStruct_FActiveSoundDiagnostic_Statics::NewProp_bSpatializationEnabled_SetBit(void* Obj)
	{
		((FActiveSoundDiagnostic*)Obj)->bSpatializationEnabled = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FActiveSoundDiagnostic_Statics::NewProp_bSpatializationEnabled = { "bSpatializationEnabled", nullptr, (EPropertyFlags)0x0010000000020001, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FActiveSoundDiagnostic), &Z_Construct_UScriptStruct_FActiveSoundDiagnostic_Statics::NewProp_bSpatializationEnabled_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FActiveSoundDiagnostic_Statics::NewProp_bSpatializationEnabled_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FActiveSoundDiagnostic_Statics::NewProp_bSpatializationEnabled_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FActiveSoundDiagnostic_Statics::NewProp_Position_MetaData[] = {
		{ "Category", "Active Sound" },
		{ "Comment", "/// Position of the sound source\n" },
		{ "ModuleRelativePath", "Private/StkDiagnostics.h" },
		{ "ToolTip", "Position of the sound source" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FActiveSoundDiagnostic_Statics::NewProp_Position = { "Position", nullptr, (EPropertyFlags)0x0010000000020001, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FActiveSoundDiagnostic, Position), METADATA_PARAMS(Z_Construct_UScriptStruct_FActiveSoundDiagnostic_Statics::NewProp_Position_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FActiveSoundDiagnostic_Statics::NewProp_Position_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FActiveSoundDiagnostic_Statics::NewProp_Sample_MetaData[] = {
		{ "Category", "Active Sound" },
		{ "Comment", "/// Sample played by this source\n" },
		{ "ModuleRelativePath", "Private/StkDiagnostics.h" },
		{ "ToolTip", "Sample played by this source" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FActiveSoundDiagnostic_Statics::NewProp_Sample = { "Sample", nullptr, (EPropertyFlags)0x0010000000020001, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FActiveSoundDiagnostic, Sample), METADATA_PARAMS(Z_Construct_UScriptStruct_FActiveSoundDiagnostic_Statics::NewProp_Sample_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FActiveSoundDiagnostic_Statics::NewProp_Sample_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FActiveSoundDiagnostic_Statics::NewProp_Actor_MetaData[] = {
		{ "Category", "Active Sound" },
		{ "Comment", "/// Actor this sound source is attached to\n" },
		{ "ModuleRelativePath", "Private/StkDiagnostics.h" },
		{ "ToolTip", "Actor this sound source is attached to" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FActiveSoundDiagnostic_Statics::NewProp_Actor = { "Actor", nullptr, (EPropertyFlags)0x0010000000020001, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FActiveSoundDiagnostic, Actor), METADATA_PARAMS(Z_Construct_UScriptStruct_FActiveSoundDiagnostic_Statics::NewProp_Actor_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FActiveSoundDiagnostic_Statics::NewProp_Actor_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FActiveSoundDiagnostic_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FActiveSoundDiagnostic_Statics::NewProp_bProcessedByUnrealEngine,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FActiveSoundDiagnostic_Statics::NewProp_bProcessedBySoundToolKit,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FActiveSoundDiagnostic_Statics::NewProp_bSpatializationEnabled,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FActiveSoundDiagnostic_Statics::NewProp_Position,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FActiveSoundDiagnostic_Statics::NewProp_Sample,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FActiveSoundDiagnostic_Statics::NewProp_Actor,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FActiveSoundDiagnostic_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_StkEditorModule,
		nullptr,
		&NewStructOps,
		"ActiveSoundDiagnostic",
		sizeof(FActiveSoundDiagnostic),
		alignof(FActiveSoundDiagnostic),
		Z_Construct_UScriptStruct_FActiveSoundDiagnostic_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FActiveSoundDiagnostic_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FActiveSoundDiagnostic_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FActiveSoundDiagnostic_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FActiveSoundDiagnostic()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FActiveSoundDiagnostic_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_StkEditorModule();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("ActiveSoundDiagnostic"), sizeof(FActiveSoundDiagnostic), Get_Z_Construct_UScriptStruct_FActiveSoundDiagnostic_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FActiveSoundDiagnostic_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FActiveSoundDiagnostic_Hash() { return 4233619204U; }
class UScriptStruct* FStatusIndicator::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern STKEDITORMODULE_API uint32 Get_Z_Construct_UScriptStruct_FStatusIndicator_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FStatusIndicator, Z_Construct_UPackage__Script_StkEditorModule(), TEXT("StatusIndicator"), sizeof(FStatusIndicator), Get_Z_Construct_UScriptStruct_FStatusIndicator_Hash());
	}
	return Singleton;
}
template<> STKEDITORMODULE_API UScriptStruct* StaticStruct<FStatusIndicator>()
{
	return FStatusIndicator::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FStatusIndicator(FStatusIndicator::StaticStruct, TEXT("/Script/StkEditorModule"), TEXT("StatusIndicator"), false, nullptr, nullptr);
static struct FScriptStruct_StkEditorModule_StaticRegisterNativesFStatusIndicator
{
	FScriptStruct_StkEditorModule_StaticRegisterNativesFStatusIndicator()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("StatusIndicator")),new UScriptStruct::TCppStructOps<FStatusIndicator>);
	}
} ScriptStruct_StkEditorModule_StaticRegisterNativesFStatusIndicator;
	struct Z_Construct_UScriptStruct_FStatusIndicator_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Value_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Value;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Description_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Description;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Type_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Type;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Name_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Name;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FStatusIndicator_Statics::Struct_MetaDataParams[] = {
		{ "Comment", "/// <summary>\n/// Struct used to represent stk::StatusIndicator objects in the UE4 engine.\n/// </summary>\n" },
		{ "ModuleRelativePath", "Private/StkDiagnostics.h" },
		{ "ToolTip", "<summary>\nStruct used to represent stk::StatusIndicator objects in the UE4 engine.\n</summary>" },
	};
#endif
	void* Z_Construct_UScriptStruct_FStatusIndicator_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FStatusIndicator>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FStatusIndicator_Statics::NewProp_Value_MetaData[] = {
		{ "Category", "Indicator" },
		{ "ModuleRelativePath", "Private/StkDiagnostics.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FStatusIndicator_Statics::NewProp_Value = { "Value", nullptr, (EPropertyFlags)0x0010000000020001, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FStatusIndicator, Value), METADATA_PARAMS(Z_Construct_UScriptStruct_FStatusIndicator_Statics::NewProp_Value_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FStatusIndicator_Statics::NewProp_Value_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FStatusIndicator_Statics::NewProp_Description_MetaData[] = {
		{ "ModuleRelativePath", "Private/StkDiagnostics.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FStatusIndicator_Statics::NewProp_Description = { "Description", nullptr, (EPropertyFlags)0x0010000000000000, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FStatusIndicator, Description), METADATA_PARAMS(Z_Construct_UScriptStruct_FStatusIndicator_Statics::NewProp_Description_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FStatusIndicator_Statics::NewProp_Description_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FStatusIndicator_Statics::NewProp_Type_MetaData[] = {
		{ "ModuleRelativePath", "Private/StkDiagnostics.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FStatusIndicator_Statics::NewProp_Type = { "Type", nullptr, (EPropertyFlags)0x0010000000000000, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FStatusIndicator, Type), METADATA_PARAMS(Z_Construct_UScriptStruct_FStatusIndicator_Statics::NewProp_Type_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FStatusIndicator_Statics::NewProp_Type_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FStatusIndicator_Statics::NewProp_Name_MetaData[] = {
		{ "Category", "Indicator" },
		{ "ModuleRelativePath", "Private/StkDiagnostics.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FStatusIndicator_Statics::NewProp_Name = { "Name", nullptr, (EPropertyFlags)0x0010000000020001, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FStatusIndicator, Name), METADATA_PARAMS(Z_Construct_UScriptStruct_FStatusIndicator_Statics::NewProp_Name_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FStatusIndicator_Statics::NewProp_Name_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FStatusIndicator_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FStatusIndicator_Statics::NewProp_Value,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FStatusIndicator_Statics::NewProp_Description,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FStatusIndicator_Statics::NewProp_Type,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FStatusIndicator_Statics::NewProp_Name,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FStatusIndicator_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_StkEditorModule,
		nullptr,
		&NewStructOps,
		"StatusIndicator",
		sizeof(FStatusIndicator),
		alignof(FStatusIndicator),
		Z_Construct_UScriptStruct_FStatusIndicator_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FStatusIndicator_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FStatusIndicator_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FStatusIndicator_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FStatusIndicator()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FStatusIndicator_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_StkEditorModule();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("StatusIndicator"), sizeof(FStatusIndicator), Get_Z_Construct_UScriptStruct_FStatusIndicator_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FStatusIndicator_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FStatusIndicator_Hash() { return 3082614698U; }
	void AStkDiagnostics::StaticRegisterNativesAStkDiagnostics()
	{
	}
	UClass* Z_Construct_UClass_AStkDiagnostics_NoRegister()
	{
		return AStkDiagnostics::StaticClass();
	}
	struct Z_Construct_UClass_AStkDiagnostics_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ActiveSoundsDiagnostics_MetaData[];
#endif
		static const UE4CodeGen_Private::FMapPropertyParams NewProp_ActiveSoundsDiagnostics;
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_ActiveSoundsDiagnostics_Key_KeyProp;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ActiveSoundsDiagnostics_ValueProp;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bActiveSoundsDiagnostics_MetaData[];
#endif
		static void NewProp_bActiveSoundsDiagnostics_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bActiveSoundsDiagnostics;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_StatusIndicators_MetaData[];
#endif
		static const UE4CodeGen_Private::FMapPropertyParams NewProp_StatusIndicators;
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_StatusIndicators_Key_KeyProp;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_StatusIndicators_ValueProp;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AStkDiagnostics_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_StkEditorModule,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AStkDiagnostics_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/// An actor providing diagnostic information regarding SoundToolKit engine.\n" },
		{ "HideCategories", "Actor Advanced Input Rendering LOD Replication Collision Cooking" },
		{ "IncludePath", "StkDiagnostics.h" },
		{ "ModuleRelativePath", "Private/StkDiagnostics.h" },
		{ "ToolTip", "An actor providing diagnostic information regarding SoundToolKit engine." },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AStkDiagnostics_Statics::NewProp_ActiveSoundsDiagnostics_MetaData[] = {
		{ "Category", "Diagnostics" },
		{ "Comment", "/// Holds info about sound sources that are currently active on the scene.\n/// Available only in PIE mode.\n" },
		{ "EditCondition", "bActiveSoundsDiagnostics" },
		{ "ModuleRelativePath", "Private/StkDiagnostics.h" },
		{ "ToolTip", "Holds info about sound sources that are currently active on the scene.\nAvailable only in PIE mode." },
	};
#endif
	const UE4CodeGen_Private::FMapPropertyParams Z_Construct_UClass_AStkDiagnostics_Statics::NewProp_ActiveSoundsDiagnostics = { "ActiveSoundsDiagnostics", nullptr, (EPropertyFlags)0x0010000000022001, UE4CodeGen_Private::EPropertyGenFlags::Map, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AStkDiagnostics, ActiveSoundsDiagnostics), EMapPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_AStkDiagnostics_Statics::NewProp_ActiveSoundsDiagnostics_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AStkDiagnostics_Statics::NewProp_ActiveSoundsDiagnostics_MetaData)) };
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_AStkDiagnostics_Statics::NewProp_ActiveSoundsDiagnostics_Key_KeyProp = { "ActiveSoundsDiagnostics_Key", nullptr, (EPropertyFlags)0x0000000000020001, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_AStkDiagnostics_Statics::NewProp_ActiveSoundsDiagnostics_ValueProp = { "ActiveSoundsDiagnostics", nullptr, (EPropertyFlags)0x0000000000020001, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 1, Z_Construct_UScriptStruct_FActiveSoundDiagnostic, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AStkDiagnostics_Statics::NewProp_bActiveSoundsDiagnostics_MetaData[] = {
		{ "Category", "Diagnostics" },
		{ "Comment", "/// Enables sound sources diagnostics.\n/// Available only in PIE mode.\n" },
		{ "ModuleRelativePath", "Private/StkDiagnostics.h" },
		{ "ToolTip", "Enables sound sources diagnostics.\nAvailable only in PIE mode." },
	};
#endif
	void Z_Construct_UClass_AStkDiagnostics_Statics::NewProp_bActiveSoundsDiagnostics_SetBit(void* Obj)
	{
		((AStkDiagnostics*)Obj)->bActiveSoundsDiagnostics = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AStkDiagnostics_Statics::NewProp_bActiveSoundsDiagnostics = { "bActiveSoundsDiagnostics", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(AStkDiagnostics), &Z_Construct_UClass_AStkDiagnostics_Statics::NewProp_bActiveSoundsDiagnostics_SetBit, METADATA_PARAMS(Z_Construct_UClass_AStkDiagnostics_Statics::NewProp_bActiveSoundsDiagnostics_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AStkDiagnostics_Statics::NewProp_bActiveSoundsDiagnostics_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AStkDiagnostics_Statics::NewProp_StatusIndicators_MetaData[] = {
		{ "Category", "Diagnostics" },
		{ "Comment", "/// Property holding all SoundToolKit's status indicators to facilitate displaying them.\n/// Available only in PIE mode.\n" },
		{ "ModuleRelativePath", "Private/StkDiagnostics.h" },
		{ "ToolTip", "Property holding all SoundToolKit's status indicators to facilitate displaying them.\nAvailable only in PIE mode." },
	};
#endif
	const UE4CodeGen_Private::FMapPropertyParams Z_Construct_UClass_AStkDiagnostics_Statics::NewProp_StatusIndicators = { "StatusIndicators", nullptr, (EPropertyFlags)0x0010000000022001, UE4CodeGen_Private::EPropertyGenFlags::Map, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AStkDiagnostics, StatusIndicators), EMapPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_AStkDiagnostics_Statics::NewProp_StatusIndicators_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AStkDiagnostics_Statics::NewProp_StatusIndicators_MetaData)) };
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_AStkDiagnostics_Statics::NewProp_StatusIndicators_Key_KeyProp = { "StatusIndicators_Key", nullptr, (EPropertyFlags)0x0000000000020001, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_AStkDiagnostics_Statics::NewProp_StatusIndicators_ValueProp = { "StatusIndicators", nullptr, (EPropertyFlags)0x0000000000020001, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 1, Z_Construct_UScriptStruct_FStatusIndicator, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AStkDiagnostics_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AStkDiagnostics_Statics::NewProp_ActiveSoundsDiagnostics,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AStkDiagnostics_Statics::NewProp_ActiveSoundsDiagnostics_Key_KeyProp,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AStkDiagnostics_Statics::NewProp_ActiveSoundsDiagnostics_ValueProp,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AStkDiagnostics_Statics::NewProp_bActiveSoundsDiagnostics,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AStkDiagnostics_Statics::NewProp_StatusIndicators,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AStkDiagnostics_Statics::NewProp_StatusIndicators_Key_KeyProp,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AStkDiagnostics_Statics::NewProp_StatusIndicators_ValueProp,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AStkDiagnostics_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AStkDiagnostics>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AStkDiagnostics_Statics::ClassParams = {
		&AStkDiagnostics::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_AStkDiagnostics_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_AStkDiagnostics_Statics::PropPointers),
		0,
		0x008000A4u,
		METADATA_PARAMS(Z_Construct_UClass_AStkDiagnostics_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AStkDiagnostics_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AStkDiagnostics()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AStkDiagnostics_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AStkDiagnostics, 4000512798);
	template<> STKEDITORMODULE_API UClass* StaticClass<AStkDiagnostics>()
	{
		return AStkDiagnostics::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AStkDiagnostics(Z_Construct_UClass_AStkDiagnostics, &AStkDiagnostics::StaticClass, TEXT("/Script/StkEditorModule"), TEXT("AStkDiagnostics"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AStkDiagnostics);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
