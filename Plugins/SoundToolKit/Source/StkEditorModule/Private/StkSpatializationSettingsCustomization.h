//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#include "IDetailCustomization.h"
#include "Layout/Visibility.h"
#include "PropertyHandle.h"

#pragma once

namespace SoundToolKit
{
	class FStkSpatializationSettingsCustomization : public IDetailCustomization
	{
	public:
		// IDetailCustomization interface
		static TSharedRef<IDetailCustomization> MakeInstance();
		virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;
		// End of IDetailCustomization interface

	protected:
		/// <summary>
		/// Used to determine if curve editor should be visible.
		/// </summary>
		/// <returns>Hidden or visible, depending on the attenuation type chosen</returns>
		EVisibility IsCustomAirAbsorptionCurveSelected() const;

		/// <summary>
		/// Used to determine if Inner Radius property should be visible.
		/// </summary>
		/// <returns>Hidden or visible, depending on the attenuation type chosen</returns>
		EVisibility IsRadiusUsed() const;

		/// <summary>
		/// Used to determine if Falloff Distance property should be visible.
		/// </summary>
		/// <returns>Hidden or visible, depending on the attenuation type chosen</returns>
		EVisibility IsFallofDistanceUsed() const;

		// Handles to StkSpatializationSettings' UPROPERTIES
		TSharedPtr<IPropertyHandle> AttenuationMethodHandle;
		TSharedPtr<IPropertyHandle> CustomAttenuationHandle;
		TSharedPtr<IPropertyHandle> FallofDistanceHandle;
		TSharedPtr<IPropertyHandle> InnerRadiusHandle;
		TSharedPtr<IPropertyHandle> UseHrtfHandle;
	};
}
