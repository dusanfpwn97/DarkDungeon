//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#include "StkSpatializationSettingsCustomization.h"
#include "StkSpatializationSourceSettings.h" 
#include "StkAttenuation.h"
#include "DetailLayoutBuilder.h"

#define LOCTEXT_NAMESPACE "StkSpatializationSettingsCustomization"

namespace SoundToolKit
{
	TSharedRef<IDetailCustomization> FStkSpatializationSettingsCustomization::MakeInstance()
	{
		return MakeShareable(new FStkSpatializationSettingsCustomization);
	}

	void FStkSpatializationSettingsCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
	{
		AttenuationMethodHandle = DetailBuilder.GetProperty(FName("Attenuation"), UStkSpatializationSourceSettings::StaticClass());
		InnerRadiusHandle = DetailBuilder.GetProperty(FName("InnerRadius"), UStkSpatializationSourceSettings::StaticClass());
		FallofDistanceHandle = DetailBuilder.GetProperty(FName("FallofDistance"), UStkSpatializationSourceSettings::StaticClass());
		CustomAttenuationHandle = DetailBuilder.GetProperty(FName("CustomAttenuation"), UStkSpatializationSourceSettings::StaticClass());
		UseHrtfHandle = DetailBuilder.GetProperty(FName("bUseHrtfSpatialization"), UStkSpatializationSourceSettings::StaticClass());

		DetailBuilder.AddPropertyToCategory(AttenuationMethodHandle);
		DetailBuilder.AddPropertyToCategory(CustomAttenuationHandle)
			.Visibility(TAttribute<EVisibility>(this, &FStkSpatializationSettingsCustomization::IsCustomAirAbsorptionCurveSelected));
		DetailBuilder.AddPropertyToCategory(InnerRadiusHandle)
			.Visibility(TAttribute<EVisibility>(this, &FStkSpatializationSettingsCustomization::IsRadiusUsed));
		DetailBuilder.AddPropertyToCategory(FallofDistanceHandle)
			.Visibility(TAttribute<EVisibility>(this, &FStkSpatializationSettingsCustomization::IsFallofDistanceUsed));
		DetailBuilder.AddPropertyToCategory(UseHrtfHandle);
	}

	EVisibility FStkSpatializationSettingsCustomization::IsCustomAirAbsorptionCurveSelected() const
	{
		uint8 MethodValue;
		AttenuationMethodHandle->GetValue(MethodValue);

		const EStkAttenuationFunction MethodType = static_cast<EStkAttenuationFunction>(MethodValue);

		return MethodType == EStkAttenuationFunction::StkAttenuation_Custom ? EVisibility::Visible : EVisibility::Hidden;
	}

	EVisibility FStkSpatializationSettingsCustomization::IsRadiusUsed() const
	{
		uint8 MethodValue;
		AttenuationMethodHandle->GetValue(MethodValue);

		const EStkAttenuationFunction MethodType = static_cast<EStkAttenuationFunction>(MethodValue);

		return MethodType == EStkAttenuationFunction::StkAttenuation_Nothing ? EVisibility::Hidden : EVisibility::Visible;
	}

	EVisibility FStkSpatializationSettingsCustomization::IsFallofDistanceUsed() const
	{
		uint8 MethodValue;
		AttenuationMethodHandle->GetValue(MethodValue);

		const EStkAttenuationFunction MethodType = static_cast<EStkAttenuationFunction>(MethodValue);

		if (MethodType == EStkAttenuationFunction::StkAttenuation_Nothing ||
			MethodType == EStkAttenuationFunction::StkAttenuation_LineSource ||
			MethodType == EStkAttenuationFunction::StkAttenuation_PointSource)
		{
			return EVisibility::Hidden;
		}
		else
		{
			return EVisibility::Visible;
		}
	}
}

#undef LOCTEXT_NAMESPACE
