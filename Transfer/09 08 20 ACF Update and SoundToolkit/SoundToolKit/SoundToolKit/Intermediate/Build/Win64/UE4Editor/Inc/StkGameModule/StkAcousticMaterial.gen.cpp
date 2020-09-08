// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "StkGameModule/Private/StkAcousticMaterial.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeStkAcousticMaterial() {}
// Cross Module References
	STKGAMEMODULE_API UEnum* Z_Construct_UEnum_StkGameModule_EStkMaterialType();
	UPackage* Z_Construct_UPackage__Script_StkGameModule();
	STKGAMEMODULE_API UClass* Z_Construct_UClass_UStkAcousticMaterial_NoRegister();
	STKGAMEMODULE_API UClass* Z_Construct_UClass_UStkAcousticMaterial();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	STKGAMEMODULE_API UScriptStruct* Z_Construct_UScriptStruct_FStkEffectCoefficients();
// End Cross Module References
	static UEnum* EStkMaterialType_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_StkGameModule_EStkMaterialType, Z_Construct_UPackage__Script_StkGameModule(), TEXT("EStkMaterialType"));
		}
		return Singleton;
	}
	template<> STKGAMEMODULE_API UEnum* StaticEnum<EStkMaterialType>()
	{
		return EStkMaterialType_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_EStkMaterialType(EStkMaterialType_StaticEnum, TEXT("/Script/StkGameModule"), TEXT("EStkMaterialType"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_StkGameModule_EStkMaterialType_Hash() { return 2777829480U; }
	UEnum* Z_Construct_UEnum_StkGameModule_EStkMaterialType()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_StkGameModule();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("EStkMaterialType"), 0, Get_Z_Construct_UEnum_StkGameModule_EStkMaterialType_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "EStkMaterialType::Predefined", (int64)EStkMaterialType::Predefined },
				{ "EStkMaterialType::Custom", (int64)EStkMaterialType::Custom },
			};
#if WITH_METADATA
			const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "Custom.Name", "EStkMaterialType::Custom" },
				{ "ModuleRelativePath", "Private/StkAcousticMaterial.h" },
				{ "Predefined.Name", "EStkMaterialType::Predefined" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_StkGameModule,
				nullptr,
				"EStkMaterialType",
				"EStkMaterialType",
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
	void UStkAcousticMaterial::StaticRegisterNativesUStkAcousticMaterial()
	{
	}
	UClass* Z_Construct_UClass_UStkAcousticMaterial_NoRegister()
	{
		return UStkAcousticMaterial::StaticClass();
	}
	struct Z_Construct_UClass_UStkAcousticMaterial_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Type_MetaData[];
#endif
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_Type;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_Type_Underlying;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Transmission_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Transmission;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bEnableTransmission_MetaData[];
#endif
		static void NewProp_bEnableTransmission_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bEnableTransmission;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Scattering_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Scattering;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bEnableScattering_MetaData[];
#endif
		static void NewProp_bEnableScattering_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bEnableScattering;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Absorption_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Absorption;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bEnableAbsorption_MetaData[];
#endif
		static void NewProp_bEnableAbsorption_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bEnableAbsorption;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UStkAcousticMaterial_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_StkGameModule,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UStkAcousticMaterial_Statics::Class_MetaDataParams[] = {
		{ "Comment", "///\x09""Class representing acoustical material asset.\n" },
		{ "IncludePath", "StkAcousticMaterial.h" },
		{ "ModuleRelativePath", "Private/StkAcousticMaterial.h" },
		{ "ToolTip", "Class representing acoustical material asset." },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UStkAcousticMaterial_Statics::NewProp_Type_MetaData[] = {
		{ "Comment", "/// <summary>\n/// Defines the material type. Only the Custom Material's parameters can be edited from GUI.\n/// </summary>\n" },
		{ "ModuleRelativePath", "Private/StkAcousticMaterial.h" },
		{ "ToolTip", "<summary>\nDefines the material type. Only the Custom Material's parameters can be edited from GUI.\n</summary>" },
	};
#endif
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UStkAcousticMaterial_Statics::NewProp_Type = { "Type", nullptr, (EPropertyFlags)0x0040000000000000, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UStkAcousticMaterial, Type), Z_Construct_UEnum_StkGameModule_EStkMaterialType, METADATA_PARAMS(Z_Construct_UClass_UStkAcousticMaterial_Statics::NewProp_Type_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UStkAcousticMaterial_Statics::NewProp_Type_MetaData)) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UClass_UStkAcousticMaterial_Statics::NewProp_Type_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UStkAcousticMaterial_Statics::NewProp_Transmission_MetaData[] = {
		{ "Category", "Effects Control" },
		{ "Comment", "/// Controls the transmission effect coefficients.\n" },
		{ "ModuleRelativePath", "Private/StkAcousticMaterial.h" },
		{ "ToolTip", "Controls the transmission effect coefficients." },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_UStkAcousticMaterial_Statics::NewProp_Transmission = { "Transmission", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UStkAcousticMaterial, Transmission), Z_Construct_UScriptStruct_FStkEffectCoefficients, METADATA_PARAMS(Z_Construct_UClass_UStkAcousticMaterial_Statics::NewProp_Transmission_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UStkAcousticMaterial_Statics::NewProp_Transmission_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UStkAcousticMaterial_Statics::NewProp_bEnableTransmission_MetaData[] = {
		{ "Category", "Effects Control" },
		{ "Comment", "/// Enables transmission of sound through walls on contact with this Material.\n" },
		{ "ModuleRelativePath", "Private/StkAcousticMaterial.h" },
		{ "ToolTip", "Enables transmission of sound through walls on contact with this Material." },
	};
#endif
	void Z_Construct_UClass_UStkAcousticMaterial_Statics::NewProp_bEnableTransmission_SetBit(void* Obj)
	{
		((UStkAcousticMaterial*)Obj)->bEnableTransmission = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UStkAcousticMaterial_Statics::NewProp_bEnableTransmission = { "bEnableTransmission", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UStkAcousticMaterial), &Z_Construct_UClass_UStkAcousticMaterial_Statics::NewProp_bEnableTransmission_SetBit, METADATA_PARAMS(Z_Construct_UClass_UStkAcousticMaterial_Statics::NewProp_bEnableTransmission_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UStkAcousticMaterial_Statics::NewProp_bEnableTransmission_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UStkAcousticMaterial_Statics::NewProp_Scattering_MetaData[] = {
		{ "Category", "Effects Control" },
		{ "Comment", "/// Controls the scattering effect coefficients.\n" },
		{ "ModuleRelativePath", "Private/StkAcousticMaterial.h" },
		{ "ToolTip", "Controls the scattering effect coefficients." },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_UStkAcousticMaterial_Statics::NewProp_Scattering = { "Scattering", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UStkAcousticMaterial, Scattering), Z_Construct_UScriptStruct_FStkEffectCoefficients, METADATA_PARAMS(Z_Construct_UClass_UStkAcousticMaterial_Statics::NewProp_Scattering_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UStkAcousticMaterial_Statics::NewProp_Scattering_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UStkAcousticMaterial_Statics::NewProp_bEnableScattering_MetaData[] = {
		{ "Category", "Effects Control" },
		{ "Comment", "/// Enables scattering of sound on contact with this Material.\n" },
		{ "ModuleRelativePath", "Private/StkAcousticMaterial.h" },
		{ "ToolTip", "Enables scattering of sound on contact with this Material." },
	};
#endif
	void Z_Construct_UClass_UStkAcousticMaterial_Statics::NewProp_bEnableScattering_SetBit(void* Obj)
	{
		((UStkAcousticMaterial*)Obj)->bEnableScattering = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UStkAcousticMaterial_Statics::NewProp_bEnableScattering = { "bEnableScattering", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UStkAcousticMaterial), &Z_Construct_UClass_UStkAcousticMaterial_Statics::NewProp_bEnableScattering_SetBit, METADATA_PARAMS(Z_Construct_UClass_UStkAcousticMaterial_Statics::NewProp_bEnableScattering_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UStkAcousticMaterial_Statics::NewProp_bEnableScattering_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UStkAcousticMaterial_Statics::NewProp_Absorption_MetaData[] = {
		{ "Category", "Effects Control" },
		{ "Comment", "/// Controls the absorption effect coefficients.\n" },
		{ "ModuleRelativePath", "Private/StkAcousticMaterial.h" },
		{ "ToolTip", "Controls the absorption effect coefficients." },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_UStkAcousticMaterial_Statics::NewProp_Absorption = { "Absorption", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UStkAcousticMaterial, Absorption), Z_Construct_UScriptStruct_FStkEffectCoefficients, METADATA_PARAMS(Z_Construct_UClass_UStkAcousticMaterial_Statics::NewProp_Absorption_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UStkAcousticMaterial_Statics::NewProp_Absorption_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UStkAcousticMaterial_Statics::NewProp_bEnableAbsorption_MetaData[] = {
		{ "Category", "Effects Control" },
		{ "Comment", "/// Enables absorption of sound on contact with this Material.\n" },
		{ "ModuleRelativePath", "Private/StkAcousticMaterial.h" },
		{ "ToolTip", "Enables absorption of sound on contact with this Material." },
	};
#endif
	void Z_Construct_UClass_UStkAcousticMaterial_Statics::NewProp_bEnableAbsorption_SetBit(void* Obj)
	{
		((UStkAcousticMaterial*)Obj)->bEnableAbsorption = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UStkAcousticMaterial_Statics::NewProp_bEnableAbsorption = { "bEnableAbsorption", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UStkAcousticMaterial), &Z_Construct_UClass_UStkAcousticMaterial_Statics::NewProp_bEnableAbsorption_SetBit, METADATA_PARAMS(Z_Construct_UClass_UStkAcousticMaterial_Statics::NewProp_bEnableAbsorption_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UStkAcousticMaterial_Statics::NewProp_bEnableAbsorption_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UStkAcousticMaterial_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UStkAcousticMaterial_Statics::NewProp_Type,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UStkAcousticMaterial_Statics::NewProp_Type_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UStkAcousticMaterial_Statics::NewProp_Transmission,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UStkAcousticMaterial_Statics::NewProp_bEnableTransmission,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UStkAcousticMaterial_Statics::NewProp_Scattering,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UStkAcousticMaterial_Statics::NewProp_bEnableScattering,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UStkAcousticMaterial_Statics::NewProp_Absorption,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UStkAcousticMaterial_Statics::NewProp_bEnableAbsorption,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UStkAcousticMaterial_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UStkAcousticMaterial>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UStkAcousticMaterial_Statics::ClassParams = {
		&UStkAcousticMaterial::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UStkAcousticMaterial_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UStkAcousticMaterial_Statics::PropPointers),
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UStkAcousticMaterial_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UStkAcousticMaterial_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UStkAcousticMaterial()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UStkAcousticMaterial_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UStkAcousticMaterial, 164008948);
	template<> STKGAMEMODULE_API UClass* StaticClass<UStkAcousticMaterial>()
	{
		return UStkAcousticMaterial::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UStkAcousticMaterial(Z_Construct_UClass_UStkAcousticMaterial, &UStkAcousticMaterial::StaticClass, TEXT("/Script/StkGameModule"), TEXT("UStkAcousticMaterial"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UStkAcousticMaterial);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
