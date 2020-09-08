//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#pragma once

#include "IAudioExtensionPlugin.h"

#include "StkOcclusionSourceSettings.generated.h"

UCLASS()
class STKGAMEMODULE_API UStkOcclusionSourceSettings : public UOcclusionPluginSourceSettingsBase
{
	GENERATED_BODY()

public:
	UStkOcclusionSourceSettings();

	/// Whether or not the sound from source can be reflected from acoustic obstacles.
	UPROPERTY(EditAnywhere, Category = "Occlusion Effects")
	bool bReflectionEnabled;

	/// Whether or not the sound from source can be transmitted through the acoustic obstacles.
	UPROPERTY(EditAnywhere, Category = "Occlusion Effects")
	bool bTransmissionEnabled;

	/// Whether or not the sound from source can be diffrated at the edges.
	UPROPERTY(EditAnywhere, Category = "Occlusion Effects")
	bool bDiffractionEnabled;
};
