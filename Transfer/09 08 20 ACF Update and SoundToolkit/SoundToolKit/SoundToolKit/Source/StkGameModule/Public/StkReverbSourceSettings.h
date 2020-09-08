//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#pragma once

#include "IAudioExtensionPlugin.h"

#include "StkReverbSourceSettings.generated.h"

UCLASS()
class STKGAMEMODULE_API UStkReverbSourceSettings : public UReverbPluginSourceSettingsBase
{
	GENERATED_BODY()

public:
	UStkReverbSourceSettings();

	/// Whether or not the source should be reverb input.
	UPROPERTY(EditAnywhere, Category = "Reverb Effect")
	bool bReverbEnabled;
};
