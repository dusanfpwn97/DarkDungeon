//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "StkEffectCoefficients.h"
#include "StkBlueprintFunctionLibrary.generated.h"

UCLASS()
class STKGAMEMODULE_API UStkBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	/// Sets the master volume scale on the scene for all sound sources processed by SoundToolKit.
	/// Volume level should be in range [0, 4], other values are clamped.
	UFUNCTION(BlueprintCallable, Category = "Volume")
	static void StkSetMasterVolume(float Volume);

	/// Gets the master volume scale on the scene for all sound sources processed by SoundToolKit.
	/// Volume level is a value in range [0, 4].
	UFUNCTION(BlueprintCallable, Category = "Volume")
	static float StkGetMasterVolume();

	/// Sets the spatial volume scale on the scene for all sound sources processed by SoundToolKit.
	/// Volume level should be in range [0, 4], other values are clamped.
	UFUNCTION(BlueprintCallable, Category = "Volume")
	static void StkSetSpatialVolume(float Volume);

	/// Gets the spatial volume scale on the scene for all sound sources processed by SoundToolKit.
	/// Volume level is a value in range [0, 4].
	UFUNCTION(BlueprintCallable, Category = "Volume")
	static float StkGetSpatialVolume();

	/// Sets the reverb volume scale on the scene for all sound sources processed by SoundToolKit.
	/// Volume level should be in range [0, 4], other values are clamped.
	UFUNCTION(BlueprintCallable, Category = "Volume")
	static void StkSetReverbVolume(float Volume);

	/// Gets the reverb volume scale on the scene for all sound sources processed by SoundToolKit.
	/// Volume level is a value in range [0, 4].
	UFUNCTION(BlueprintCallable, Category = "Volume")
	static float StkGetReverbVolume();

	/// Enables global HRTF spatialization on the scene for all sound sources processed by SoundToolKit.
	/// The HRTF effect is still disabled for sound sources that have this flag disabled in StkSpatialSourceSettings.
	UFUNCTION(BlueprintCallable, Category = "Spatial Effects")
	static void StkEnableHrtf();

	/// Disables global HRTF spatialization on the scene for all sound sources processed by SoundToolKit.
	/// This disables HRTF for the entire scene, for all sound sources, even if HRTF is enabled for particular sound source in StkSpatialSourceSettings.
	UFUNCTION(BlueprintCallable, Category = "Spatial Effects")
	static void StkDisableHrtf();

	/// Checks if global HRTF spatialization is enabled on the scene for all sound sources processed by SoundToolKit.
	UFUNCTION(BlueprintCallable, Category = "Spatial Effects")
	static bool StkIsHrtfEnabled();

	/// Enables global attenuation of sound with distance on the scene for all sound sources processed by SoundToolKit.
	UFUNCTION(BlueprintCallable, Category = "Spatial Effects")
	static void StkEnableAttenuation();

	/// Disables global attenuation of sound with distance on the scene for all sound sources processed by SoundToolKit.
	UFUNCTION(BlueprintCallable, Category = "Spatial Effects")
	static void StkDisableAttenuation();

	/// Checks if global attenuation of sound with distance is enabled on the scene for all sound sources processed by SoundToolKit.
	UFUNCTION(BlueprintCallable, Category = "Spatial Effects")
	static bool StkIsAttenuationEnabled();

	/// Enables global specular reflection of sound from obstacles on the scene for all sound sources processed by SoundToolKit.
	/// The reflection effect is still disabled for sound sources that have this flag disabled in StkOcclusionSourceSettings.
	UFUNCTION(BlueprintCallable, Category = "Occlusion Effects")
	static void StkEnableReflection();

	/// Disables global specular reflection of sound from obstacles on the scene for all sound sources processed by SoundToolKit.
	/// This disables reflection effect for the entire scene, for all sound sources, even if reflection is enabled for particular sound source in StkOcclusionSourceSettings.
	UFUNCTION(BlueprintCallable, Category = "Occlusion Effects")
	static void StkDisableReflection();

	/// Checks if global specular reflection of sound from obstacles is enabled on the scene for all sound sources processed by SoundToolKit.
	UFUNCTION(BlueprintCallable, Category = "Occlusion Effects")
	static bool StkIsReflectionEnabled();

	/// Enables global transmission of sound through obstacles on the scene for all sound sources processed by SoundToolKit.
	/// The transmission effect is still disabled for sound sources that have this flag disabled in StkOcclusionSourceSettings.
	UFUNCTION(BlueprintCallable, Category = "Occlusion Effects")
	static void StkEnableTransmission();

	/// Disables global transmission of sound through obstacles on the scene for all sound sources processed by SoundToolKit.
	/// This disables transmission effect for the entire scene, for all sound sources, even if transmission is enabled for particular sound source in StkOcclusionSourceSettings.
	UFUNCTION(BlueprintCallable, Category = "Occlusion Effects")
	static void StkDisableTransmission();

	/// Checks if global transmission of sound through obstacles is enabled on the scene for all sound sources processed by SoundToolKit.
	UFUNCTION(BlueprintCallable, Category = "Occlusion Effects")
	static bool StkIsTransmissionEnabled();

	/// Enables global diffraction of sound on edges on the scene for all sound sources processed by SoundToolKit.
	/// The diffraction effect is still disabled for sound sources that have this flag disabled in StkOcclusionSourceSettings.
	UFUNCTION(BlueprintCallable, Category = "Occlusion Effects")
	static void StkEnableDiffraction();

	/// Disables global diffraction of sound on edges on the scene for all sound sources processed by SoundToolKit.
	/// This disables diffraction effect for the entire scene, for all sound sources, even if diffraction is enabled for particular sound source in StkOcclusionSourceSettings.
	UFUNCTION(BlueprintCallable, Category = "Occlusion Effects")
	static void StkDisableDiffraction();

	/// Checks if global diffraction of sound on edges is enabled on the scene for all sound sources processed by SoundToolKit.
	UFUNCTION(BlueprintCallable, Category = "Occlusion Effects")
	static bool StkIsDiffractionEnabled();

	/// Sets the speed of sound in a given acoustic medium [m/s] on the scene for all sound sources processed by SoundToolKit.
	/// Speed of sound value should be in range [100, 1000], other values are clamped.
	UFUNCTION(BlueprintCallable, Category = "Acoustic Medium")
	static void StkSetSpeedOfSound(float SpeedOfSound);

	/// Gets the speed of sound in a given acoustic medium [m/s] on the scene for all sound sources processed by SoundToolKit.
	/// Speed of sound value is a value in range [100, 1000].
	UFUNCTION(BlueprintCallable, Category = "Acoustic Medium")
	static float StkGetSpeedOfSound();

	/// Enables attenuation due to acoustic medium viscosity on the scene for all sound sources processed by SoundToolKit.
	UFUNCTION(BlueprintCallable, Category = "Acoustic Medium")
	static void StkEnableDamping();

	/// Disables attenuation due to acoustic medium viscosity on the scene for all sound sources processed by SoundToolKit.
	UFUNCTION(BlueprintCallable, Category = "Acoustic Medium")
	static void StkDisableDamping();

	/// Checks if attenuation due to acoustic medium viscosity is enabled on the scene for all sound sources processed by SoundToolKit.
	UFUNCTION(BlueprintCallable, Category = "Acoustic Medium")
	static bool StkIsDampingEnabled();

	/// Sets the coefficients for attenuation due to medium viscosity on the scene for all sound sources processed by SoundToolKit.
	/// Coefficient value for every band should be in range [0, 1], other values are clamped.
	UFUNCTION(BlueprintCallable, Category = "Acoustic Medium")
	static void StkSetDampingCoefficients(FStkEffectCoefficients DampingCoefficients);

	/// Gets the coefficients for attenuation due to medium viscosity on the scene for all sound sources processed by SoundToolKit.
	/// Coefficient value for each band is in range [0, 1].
	UFUNCTION(BlueprintCallable, Category = "Acoustic Medium")
	static FStkEffectCoefficients StkGetDampingCoefficients();
};
