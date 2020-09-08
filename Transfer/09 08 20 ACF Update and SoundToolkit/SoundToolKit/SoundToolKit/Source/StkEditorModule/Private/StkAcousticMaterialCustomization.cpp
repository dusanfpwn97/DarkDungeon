//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#include "StkAcousticMaterialCustomization.h"
#include "DetailLayoutBuilder.h"
#include "DetailCategoryBuilder.h"
#include "Widgets/Text/STextBlock.h"
#include "PropertyCustomizationHelpers.h"
#include "ScopedTransaction.h"

#define LOCTEXT_NAMESPACE "StkAcousticMaterialCustomization"

namespace SoundToolKit
{
	TSharedRef<IDetailCustomization> FStkAcousticMaterialCustomization::MakeInstance()
	{
		return MakeShareable(new FStkAcousticMaterialCustomization);
	}

	void FStkAcousticMaterialCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
	{
		const TArray<TWeakObjectPtr<UObject>>& SelectedObjects = DetailBuilder.GetSelectedObjects();
		for (const TWeakObjectPtr<UObject>& Object : SelectedObjects)
		{
			if (Object.IsValid())
			{
				UStkAcousticMaterial* StkMaterialPtr = Cast<UStkAcousticMaterial>(Object.Get());
				if (StkMaterialPtr)
				{
					StkMaterial = StkMaterialPtr;
					break;
				}
			}
		}

		TypeHandle = DetailBuilder.GetProperty(FName("Type"), UStkAcousticMaterial::StaticClass());
		bEnableAbsorptionHandle = DetailBuilder.GetProperty(FName("bEnableAbsorption"), UStkAcousticMaterial::StaticClass());
		AbsorptionHandle = DetailBuilder.GetProperty(FName("Absorption"), UStkAcousticMaterial::StaticClass());
		bEnableScatteringHandle = DetailBuilder.GetProperty(FName("bEnableScattering"), UStkAcousticMaterial::StaticClass());
		ScatteringHandle = DetailBuilder.GetProperty(FName("Scattering"), UStkAcousticMaterial::StaticClass());
		bEnableTransmissionHandle = DetailBuilder.GetProperty(FName("bEnableTransmission"), UStkAcousticMaterial::StaticClass());
		TransmissionHandle = DetailBuilder.GetProperty(FName("Transmission"), UStkAcousticMaterial::StaticClass());

		if (StkMaterial->IsCustom())
		{
			FText ToolTipText = FText::FromString(TEXT("Sets the Effects Control values to those of selected AcousticMaterial."));

			DetailBuilder.EditCategory(TEXT("Effects Control")).AddCustomRow(FText::FromString(TEXT("Effects Control")))
				.NameContent()
				[
					SNew(STextBlock)
					.Text(FText::FromString(TEXT("Preset")))
					.ToolTipText(ToolTipText)
				]
				.ValueContent()
				[
					SNew(SObjectPropertyEntryBox)
					.AllowedClass(UStkAcousticMaterial::StaticClass())
					.OnObjectChanged_Lambda([&StkMaterial = StkMaterial, &CurrentPresetPath = CurrentPresetPath](const FAssetData& AssetData)
					{
						{
							const FScopedTransaction Transaction(
								FText::FromString(TEXT("Preset ") + StkMaterial->GetName() + TEXT(" with ") + AssetData.AssetName.ToString()));
							StkMaterial->Modify();

							StkMaterial->SetProperties(Cast<UStkAcousticMaterial>(AssetData.GetAsset()));
						}
						CurrentPresetPath = AssetData.ObjectPath.ToString();
					})
					.NewAssetFactories(TArray<UFactory*>())
					.ObjectPath_Lambda([&CurrentPresetPath = CurrentPresetPath] { return CurrentPresetPath; })
					.ToolTipText(ToolTipText)
				].ValueWidget.MinDesiredWidth(300.0f);
		}

		DetailBuilder.AddPropertyToCategory(bEnableAbsorptionHandle)
			.EditCondition(TAttribute<bool>(this, &FStkAcousticMaterialCustomization::AreTogglesEditable), nullptr);

		DetailBuilder.AddPropertyToCategory(AbsorptionHandle)
			.EditCondition(TAttribute<bool>(this, &FStkAcousticMaterialCustomization::IsAbsorptionEditable), nullptr)
			.ShouldAutoExpand();

		DetailBuilder.AddPropertyToCategory(bEnableScatteringHandle)
			.EditCondition(TAttribute<bool>(this, &FStkAcousticMaterialCustomization::AreTogglesEditable), nullptr);

		DetailBuilder.AddPropertyToCategory(ScatteringHandle)
			.EditCondition(TAttribute<bool>(this, &FStkAcousticMaterialCustomization::IsScatteringEditable), nullptr)
			.ShouldAutoExpand();

		DetailBuilder.AddPropertyToCategory(bEnableTransmissionHandle)
			.EditCondition(TAttribute<bool>(this, &FStkAcousticMaterialCustomization::AreTogglesEditable), nullptr);

		DetailBuilder.AddPropertyToCategory(TransmissionHandle)
			.EditCondition(TAttribute<bool>(this, &FStkAcousticMaterialCustomization::IsTransmissionEditable), nullptr)
			.ShouldAutoExpand();
	}

	EVisibility FStkAcousticMaterialCustomization::IsCustom() const
	{
		return StkMaterial->IsCustom() ? EVisibility::Visible : EVisibility::Hidden;
	}

	bool FStkAcousticMaterialCustomization::AreTogglesEditable() const
	{
		return StkMaterial->IsCustom();
	}

	bool FStkAcousticMaterialCustomization::IsAbsorptionEditable() const
	{
		return StkMaterial->IsCustom() && StkMaterial->bEnableAbsorption;
	}

	bool FStkAcousticMaterialCustomization::IsScatteringEditable() const
	{
		return StkMaterial->IsCustom() && StkMaterial->bEnableScattering;
	}

	bool FStkAcousticMaterialCustomization::IsTransmissionEditable() const
	{
		return StkMaterial->IsCustom() && StkMaterial->bEnableTransmission;
	}
}

#undef LOCTEXT_NAMESPACE
