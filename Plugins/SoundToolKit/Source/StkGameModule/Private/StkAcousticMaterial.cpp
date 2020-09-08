//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#include "StkAcousticMaterial.h"
#include "StkCommon.h"
#include "StkMaterial.h"
#include "StkGameModule.h"
#include "StkMaterialAssetsGenerator.h"

THIRD_PARTY_INCLUDES_START
#include <stk/UniqueResource.h>
#include <stk/ISoundToolKit.h>
#include <stk/IResourcesFactory.h>
#include <stk/IMaterial.h>
#include <stk_ex/scene/MaterialsLoader.h>
#include <stk/IEffect.h>
THIRD_PARTY_INCLUDES_END

#include "Misc/Paths.h"
#include "Misc/FileHelper.h"

namespace
{
	void CopyCoefficients(FStkEffectCoefficients& Target, const stk::IEffect::Coefficients& Source)
	{
		Target.Band125Hz = Source[0];
		Target.Band250Hz = Source[1];
		Target.Band500Hz = Source[2];
		Target.Band1000Hz = Source[3];
		Target.Band2000Hz = Source[4];
		Target.Band4000Hz = Source[5];
		Target.Band8000Hz = Source[6];
		Target.Band16000Hz = Source[7];
	}

	void CopyCoefficients(FStkEffectCoefficients& Target, const FStkEffectCoefficients& Source)
	{
		Target.Band125Hz = Source.Band125Hz;
		Target.Band250Hz = Source.Band250Hz;
		Target.Band500Hz = Source.Band500Hz;
		Target.Band1000Hz = Source.Band1000Hz;
		Target.Band2000Hz = Source.Band2000Hz;
		Target.Band4000Hz = Source.Band4000Hz;
		Target.Band8000Hz = Source.Band8000Hz;
		Target.Band16000Hz = Source.Band16000Hz;
	}

	stk::IEffect::Coefficients ToStkCoefficients(const FStkEffectCoefficients& Source)
	{
		return 	stk::IEffect::Coefficients
		{
			Source.Band125Hz,
			Source.Band250Hz,
			Source.Band500Hz,
			Source.Band1000Hz,
			Source.Band2000Hz,
			Source.Band4000Hz,
			Source.Band8000Hz,
			Source.Band16000Hz
		};
	}
}

UStkAcousticMaterial::UStkAcousticMaterial()
{
	CreateInternalMaterial();
	UpdateInternalMaterial();
}

void UStkAcousticMaterial::PostLoadSubobjects(FObjectInstancingGraph* OuterInstanceGraph)
{
	Super::PostLoadSubobjects(OuterInstanceGraph);
	UpdateInternalMaterial();
}

#if WITH_EDITOR
void UStkAcousticMaterial::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	if (PropertyChangedEvent.Property && PropertyChangedEvent.MemberProperty)
	{
		const FName& PropertyName = PropertyChangedEvent.GetPropertyName();
		const FName& MemberPropertyName = PropertyChangedEvent.MemberProperty->GetFName();

		if (Material)
		{
			OnUpdateToggles(PropertyName);
			OnUpdateCoefficients(MemberPropertyName);
		}
	}
	else
	{
		UpdateInternalMaterial();
	}
}
#endif

const SoundToolKit::FStkMaterial& UStkAcousticMaterial::GetMaterial() const
{
	return *Material;
}

void UStkAcousticMaterial::LoadMaterial(const FString& JsonPath)
{
	if (Material.IsValid())
	{
		return;
	}

	FString MaterialData;
	FFileHelper::LoadFileToString(MaterialData, *JsonPath);

	stk::SharedResource<stk::IMaterial> NativeMaterial =
		stk_ex::scene::loadMaterialJsonFromMemory(*SoundToolKit::Utils::GetGameModule().GetAudio(), TCHAR_TO_ANSI(*MaterialData));

	Material = MakeUnique<SoundToolKit::FStkMaterial>(NativeMaterial);
}

void UStkAcousticMaterial::InitializeControls()
{
	Material.Get()->Native().get()->absorption().isEnabled([&bEnableAbsorption = bEnableAbsorption](bool bEnabled)
	{
		bEnableAbsorption = bEnabled;
	});

	Material.Get()->Native().get()->scattering().isEnabled([&bEnableScattering = bEnableScattering](bool bEnabled)
	{
		bEnableScattering = bEnabled;
	});

	Material.Get()->Native().get()->transmission().isEnabled([&bEnableTransmission = bEnableTransmission](bool bEnabled)
	{
		bEnableTransmission = bEnabled;
	});

	Material.Get()->Native().get()->absorption().getCoefficients([&Absorption = Absorption](const stk::IEffect::Coefficients& Coefficients)
	{
		CopyCoefficients(Absorption, Coefficients);
	});

	Material.Get()->Native().get()->scattering().getCoefficients([&Scattering = Scattering](const stk::IEffect::Coefficients& Coefficients)
	{
		CopyCoefficients(Scattering, Coefficients);
	});

	Material.Get()->Native().get()->transmission().getCoefficients([&Transmission = Transmission](const stk::IEffect::Coefficients& Coefficients)
	{
		CopyCoefficients(Transmission, Coefficients);
	});

	SoundToolKit::Utils::GetGameModule().Finish();
}

void UStkAcousticMaterial::CreateInternalMaterial()
{
	if (Material.IsValid())
	{
		return;
	}

	auto NativeMaterial = SoundToolKit::Utils::GetGameModule().GetAudio().get()->resourcesFactory().createMaterial();
	Material = MakeUnique<SoundToolKit::FStkMaterial>(NativeMaterial);
}

#if WITH_EDITOR
void UStkAcousticMaterial::OnUpdateToggles(const FName& PropertyName)
{
	if (PropertyName.IsEqual(GET_MEMBER_NAME_CHECKED(UStkAcousticMaterial, bEnableAbsorption)))
	{
		UpdateAbsorptionToggle();
	}
	else if (PropertyName.IsEqual(GET_MEMBER_NAME_CHECKED(UStkAcousticMaterial, bEnableScattering)))
	{
		UpdateScatteringToggle();
	}
	else if (PropertyName.IsEqual(GET_MEMBER_NAME_CHECKED(UStkAcousticMaterial, bEnableTransmission)))
	{
		UpdateTransmissionToggle();
	}
}

void UStkAcousticMaterial::OnUpdateCoefficients(const FName& MemberPropertyName)
{
	if (MemberPropertyName.IsEqual(GET_MEMBER_NAME_CHECKED(UStkAcousticMaterial, Absorption)))
	{
		UpdateAbsorptionCoefficients();
	}
	else if (MemberPropertyName.IsEqual(GET_MEMBER_NAME_CHECKED(UStkAcousticMaterial, Scattering)))
	{
		UpdateScatteringCoefficients();
	}
	else if (MemberPropertyName.IsEqual(GET_MEMBER_NAME_CHECKED(UStkAcousticMaterial, Transmission)))
	{
		UpdateTransmissionCoefficients();
	}
}
#endif

void UStkAcousticMaterial::UpdateInternalMaterial()
{
	if (Material.IsValid())
	{
		UpdateAbsorptionToggle();
		UpdateAbsorptionCoefficients();
		UpdateScatteringToggle();
		UpdateScatteringCoefficients();
		UpdateTransmissionToggle();
		UpdateTransmissionCoefficients();
	}
}

void UStkAcousticMaterial::UpdateAbsorptionToggle()
{
	if (bEnableAbsorption)
	{
		Material.Get()->Native().get()->absorption().enable();
	}
	else
	{
		Material.Get()->Native().get()->absorption().disable();
	}
}

void UStkAcousticMaterial::UpdateAbsorptionCoefficients()
{
	Material.Get()->Native().get()->absorption().setCoefficients(ToStkCoefficients(Absorption));
}

void UStkAcousticMaterial::UpdateScatteringToggle()
{
	if (bEnableScattering)
	{
		Material.Get()->Native().get()->scattering().enable();
	}
	else
	{
		Material.Get()->Native().get()->scattering().disable();
	}
}

void UStkAcousticMaterial::UpdateScatteringCoefficients()
{
	Material.Get()->Native().get()->scattering().setCoefficients(ToStkCoefficients(Scattering));
}

void UStkAcousticMaterial::UpdateTransmissionToggle()
{
	if (bEnableTransmission)
	{
		Material.Get()->Native().get()->transmission().enable();
	}
	else
	{
		Material.Get()->Native().get()->transmission().disable();
	}
}

void UStkAcousticMaterial::UpdateTransmissionCoefficients()
{
	Material.Get()->Native().get()->transmission().setCoefficients(ToStkCoefficients(Transmission));
}

void UStkAcousticMaterial::SetCustom()
{
	Type = EStkMaterialType::Custom;
}

bool UStkAcousticMaterial::IsCustom()
{
	return Type == EStkMaterialType::Custom;
}

void UStkAcousticMaterial::SetProperties(UStkAcousticMaterial* Preset)
{
	if (Preset != nullptr)
	{
		bEnableAbsorption = Preset->bEnableAbsorption;
		bEnableScattering = Preset->bEnableScattering;
		bEnableTransmission = Preset->bEnableTransmission;
		CopyCoefficients(Absorption, Preset->Absorption);
		CopyCoefficients(Scattering, Preset->Scattering);
		CopyCoefficients(Transmission, Preset->Transmission);
	}
	else
	{
		bEnableAbsorption = true;
		bEnableScattering = true;
		bEnableTransmission = true;
		Absorption = FStkEffectCoefficients();
		Scattering = FStkEffectCoefficients();
		Transmission = FStkEffectCoefficients();
	}

	UpdateInternalMaterial();
}
