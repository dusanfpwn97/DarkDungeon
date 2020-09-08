//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#include "StkAcousticMaterial.h"

#include "IDetailCustomization.h"
#include "Layout/Visibility.h"
#include "PropertyHandle.h"

#pragma once

namespace SoundToolKit
{
	class FStkAcousticMaterialCustomization : public IDetailCustomization
	{
	public:
		// IDetailCustomization interface
		static TSharedRef<IDetailCustomization> MakeInstance();
		virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;
		// End of IDetailCustomization interface

	protected:
		/// <summary>
		/// Used to determine whether Preset should be visible.
		/// </summary>
		EVisibility IsCustom() const;

		/// <summary>
		/// Used to determine whether Effect toggles should be editable.
		/// </summary>
		bool AreTogglesEditable() const;

		/// <summary>
		/// Used to determine whether Absorption Effect's coefficients should be editable.
		/// </summary>
		bool IsAbsorptionEditable() const;

		/// <summary>
		/// Used to determine whether Scattering Effect's coefficients should be editable.
		/// </summary>
		bool IsScatteringEditable() const;

		/// <summary>
		/// Used to determine whether Transmission Effect's coefficients should be editable.
		/// </summary>
		bool IsTransmissionEditable() const;

		/// <summary>
		/// Access point to object that's being edited.
		/// </summary>
		TWeakObjectPtr<UStkAcousticMaterial> StkMaterial;

		// Handles to StkAcousticMaterial's UPROPERTIES
		TSharedPtr<IPropertyHandle> TypeHandle;
		TSharedPtr<IPropertyHandle> bEnableAbsorptionHandle;
		TSharedPtr<IPropertyHandle> AbsorptionHandle;
		TSharedPtr<IPropertyHandle> bEnableScatteringHandle;
		TSharedPtr<IPropertyHandle> ScatteringHandle;
		TSharedPtr<IPropertyHandle> bEnableTransmissionHandle;
		TSharedPtr<IPropertyHandle> TransmissionHandle;

	private:
		FString CurrentPresetPath;
	};
}
