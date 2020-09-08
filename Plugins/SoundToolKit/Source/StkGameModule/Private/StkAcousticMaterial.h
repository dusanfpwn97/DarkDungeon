//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#pragma once

#include "StkMaterial.h"
#include "StkEffectCoefficients.h"

#include "StkAcousticMaterial.generated.h"

namespace SoundToolKit
{
	class FStkMaterial;
}

UENUM()
enum class EStkMaterialType : uint8
{
	Predefined = 0,
	Custom = 1
};

///	Class representing acoustical material asset.
UCLASS()
class STKGAMEMODULE_API UStkAcousticMaterial : public UObject
{
	GENERATED_BODY()

public:
	// UObject interface
	virtual void PostLoadSubobjects(FObjectInstancingGraph* OuterInstanceGraph) override;
#if WITH_EDITOR
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
	// End of UObject interface

	UStkAcousticMaterial();

	/// Enables absorption of sound on contact with this Material.
	UPROPERTY(EditAnywhere, Category = "Effects Control")
	bool bEnableAbsorption = true;

	/// Controls the absorption effect coefficients.
	UPROPERTY(EditAnywhere, Category = "Effects Control")
	FStkEffectCoefficients Absorption;

	/// Enables scattering of sound on contact with this Material.
	UPROPERTY(EditAnywhere, Category = "Effects Control")
	bool bEnableScattering = true;

	/// Controls the scattering effect coefficients.
	UPROPERTY(EditAnywhere, Category = "Effects Control")
	FStkEffectCoefficients Scattering;

	/// Enables transmission of sound through walls on contact with this Material.
	UPROPERTY(EditAnywhere, Category = "Effects Control")
	bool bEnableTransmission = true;

	/// Controls the transmission effect coefficients.
	UPROPERTY(EditAnywhere, Category = "Effects Control")
	FStkEffectCoefficients Transmission;

	/// <summary>
	/// Used to get reference to StkMaterial instance for this acoustic material.
	/// </summary>
	/// <returns>The associated material</returns>
	const SoundToolKit::FStkMaterial& GetMaterial() const;

	/// <summary>
	/// Loads StkMaterial based on provided path to Json configuration file.
	/// </summary>
	void LoadMaterial(const FString& JsonPath);

	/// <summary>
	/// Initializes the Material controls and coefficients.
	/// </summary>
	/// <param name="StkMaterial">The Material object that is the source of coefficients</param>
	void InitializeControls();

	/// <summary>
	/// Marks the Material as Custom thus enabling edition of Effects.
	/// </summary>
	void SetCustom();

	/// <summary>
	/// Checks if the Material is a Custom-created one.
	/// </summary>
	bool IsCustom();

	/// <summary>
	/// Sets the Material properties based on given preset Material.
	/// </summary>
	void SetProperties(UStkAcousticMaterial* Preset);

private:
	/// <summary>
	/// Creates internal StkMaterial based on current Effects Control settings.
	/// </summary>
	void CreateInternalMaterial();

#if WITH_EDITOR
	void OnUpdateToggles(const FName& PropertyName);
	void OnUpdateCoefficients(const FName& MemberPropertyName);
#endif

	void UpdateInternalMaterial();

	void UpdateAbsorptionToggle();
	void UpdateAbsorptionCoefficients();

	void UpdateScatteringToggle();
	void UpdateScatteringCoefficients();

	void UpdateTransmissionToggle();
	void UpdateTransmissionCoefficients();

	/// <summary>
	/// Defines the material type. Only the Custom Material's parameters can be edited from GUI.
	/// </summary>
	UPROPERTY()
	EStkMaterialType Type = EStkMaterialType::Predefined;

	/// <summary>
	/// An object representing this material in SoundToolKit engine.
	/// </summary>
	TUniquePtr<SoundToolKit::FStkMaterial> Material;
};
