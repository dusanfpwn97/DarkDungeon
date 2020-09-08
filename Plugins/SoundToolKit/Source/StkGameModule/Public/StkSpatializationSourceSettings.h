//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#pragma once

#include "StkAttenuation.h"

#include "IAudioExtensionPlugin.h"
#include "Curves/CurveFloat.h"

#include "StkSpatializationSourceSettings.generated.h"

UCLASS()
class STKGAMEMODULE_API UStkSpatializationSourceSettings : public USpatializationPluginSourceSettingsBase
{
	GENERATED_BODY()

public:
	UStkSpatializationSourceSettings();

	/// The attenuation with distance function to use.
	UPROPERTY(EditAnywhere, Category = "Spatial Effects")
	EStkAttenuationFunction Attenuation;

	/// The custom attenuation curve. Only range of (0,1) in both axes.
	UPROPERTY(EditAnywhere, Category = "Spatial Effects", meta = (ClampFloatTangent = "1.0"))
	FRuntimeFloatCurve CustomAttenuation;

	/// The radius of the sound source at which sound is not attenuated.
	UPROPERTY(EditAnywhere, Category = "Spatial Effects", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float InnerRadius;

	/// The distance over which sound attenuation occurs.
	UPROPERTY(EditAnywhere, Category = "Spatial Effects", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float FallofDistance;

	/// Whether or not HRTF functions should be used.
	UPROPERTY(EditAnywhere, Category = "Spatial Effects")
	bool bUseHrtfSpatialization;
};
