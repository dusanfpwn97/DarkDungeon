//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#include "StkReverb.h"
#include "StkListenerManager.h"
#include "StkReverbSourceSettings.h"
#include "StkSoundSourceManager.h"
#include "Sound/SoundSubmix.h"

namespace SoundToolKit
{
	FStkReverbFactory::FStkReverbFactory(FStkAudioOutput& AudioOutput, FStkSoundSourceManager& SoundSourceManager, FStkListenerManager& ListenerManager)
		: StkAudioOutput(AudioOutput)
		, StkSoundSourceManager(SoundSourceManager)
		, StkListenerManager(ListenerManager)
	{
	}

	FString FStkReverbFactory::GetDisplayName()
	{
		static FString DisplayName = FString(TEXT("SoundToolKit"));

		return DisplayName;
	}

#if ENGINE_MINOR_VERSION >= 24
	bool FStkReverbFactory::SupportsPlatform(const FString& PlatformName)
	{
		return PlatformName == FString(TEXT("Windows"));
	}
#else
	bool FStkReverbFactory::SupportsPlatform(EAudioPlatform Platform)
	{
		return Platform == EAudioPlatform::Windows;
	}
#endif

	TAudioReverbPtr FStkReverbFactory::CreateNewReverbPlugin(FAudioDevice* OwningDevice)
	{
		return TAudioReverbPtr(new FStkAudioReverb(StkAudioOutput, StkSoundSourceManager, StkListenerManager));
	}

	UClass* FStkReverbFactory::GetCustomReverbSettingsClass() const
	{
		return UStkReverbSourceSettings::StaticClass();
	}

	FStkAudioReverb::FStkAudioReverb(FStkAudioOutput& AudioOutput, FStkSoundSourceManager& SoundSourceManager, FStkListenerManager& ListenerManager)
		: StkAudioOutput(AudioOutput)
		, StkSoundSourceManager(SoundSourceManager)
		, StkListenerManager(ListenerManager)
		, AudioDevice(nullptr)
	{
	}

	FStkAudioReverb::~FStkAudioReverb()
	{
		StkListenerManager.UnregisterAudioDevice(AudioDevice);
	}

	void FStkAudioReverb::Initialize(const FAudioPluginInitializationParams InitializationParams)
	{
		AudioDevice = InitializationParams.AudioDevicePtr;
		StkListenerManager.RegisterAudioDevice(AudioDevice);
	}

	void FStkAudioReverb::OnInitSource(const uint32 SourceId, const FName& AudioComponentUserId, const uint32 NumChannels, UReverbPluginSourceSettingsBase* InSettings)
	{
		StkSoundSourceManager.Add(SourceId, EAudioPlugin::REVERB, InSettings);
	}

	void FStkAudioReverb::OnReleaseSource(const uint32 SourceId)
	{
		StkSoundSourceManager.Remove(SourceId, EAudioPlugin::REVERB);
	}

	FSoundEffectSubmixPtr FStkAudioReverb::GetEffectSubmix()
	{
		if (!SubmixEffect.IsValid())
		{
			UStkSubmixEffectReverbPluginPreset* ReverbPluginPreset = nullptr;
			USoundSubmix* Submix = GetSubmix();
			if (Submix->SubmixEffectChain.Num() > 0)
			{
				if (UStkSubmixEffectReverbPluginPreset* CurrentPreset = Cast<UStkSubmixEffectReverbPluginPreset>(Submix->SubmixEffectChain[0]))
				{
					ReverbPluginPreset = CurrentPreset;
				}
			}

			check(ReverbPluginPreset);

			SubmixEffect = USoundEffectPreset::CreateInstance<FSoundEffectSubmixInitData, FSoundEffectSubmix>(
				FSoundEffectSubmixInitData(), *ReverbPluginPreset);
			SubmixEffect->SetEnabled(true);
		}

		return SubmixEffect;
	}

	USoundSubmix* FStkAudioReverb::GetSubmix()
	{
		if (!ReverbSubmix.IsValid())
		{
			ReverbSubmix = NewObject<USoundSubmix>(USoundSubmix::StaticClass(), TEXT("SoundToolKit Reverb Submix"));
			ReverbSubmix->bMuteWhenBackgrounded = true;
			ReverbSubmix->SubmixEffectChain.Add(NewObject<UStkSubmixEffectReverbPluginPreset>(
				UStkSubmixEffectReverbPluginPreset::StaticClass(), TEXT("Reverb Plugin Effect Preset")));
		}

		return ReverbSubmix.Get();
	}
}

uint32 FStkSubmixEffectReverbPlugin::GetDesiredInputChannelCountOverride() const
{
	return 1u;
}
