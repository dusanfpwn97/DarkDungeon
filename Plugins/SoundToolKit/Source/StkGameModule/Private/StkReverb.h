//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#pragma once

#include "IAudioExtensionPlugin.h"
#include "Sound/SoundEffectSubmix.h"
#include "Sound/SoundEffectPreset.h"
#include "Runtime/Launch/Resources/Version.h"

#include "StkReverb.generated.h"

namespace SoundToolKit
{
	class FStkReverbFactory : public IAudioReverbFactory
	{
	public:
		FStkReverbFactory(class FStkAudioOutput& AudioOutput, class FStkSoundSourceManager& SoundSourceManager, class FStkListenerManager& ListenerManager);

		// IAudioPluginFactory interface
		virtual FString GetDisplayName() override;
#if ENGINE_MINOR_VERSION >= 24
		virtual bool SupportsPlatform(const FString& PlatformName) override;
#else
		virtual bool SupportsPlatform(EAudioPlatform Platform) override;
#endif
		// End of IAudioPluginFactory interface

		// IAudioReverbFactory interface
		virtual TAudioReverbPtr CreateNewReverbPlugin(FAudioDevice* OwningDevice) override;
		virtual UClass* GetCustomReverbSettingsClass() const override;
		// End of IAudioReverbFactory interface

	private:
		class FStkAudioOutput& StkAudioOutput;
		class FStkSoundSourceManager& StkSoundSourceManager;
		class FStkListenerManager& StkListenerManager;
	};

	class FStkAudioReverb : public IAudioReverb
	{
	public:
		FStkAudioReverb(class FStkAudioOutput& AudioOutput, class FStkSoundSourceManager& SoundSourceManager, class FStkListenerManager& ListenerManager);
		~FStkAudioReverb();

		// IAudioReverb interfacede;
		virtual void Initialize(const FAudioPluginInitializationParams InitializationParams) override;
		virtual void OnInitSource(const uint32 SourceId, const FName& AudioComponentUserId, const uint32 NumChannels, UReverbPluginSourceSettingsBase* InSettings) override;
		virtual void OnReleaseSource(const uint32 SourceId) override;
		virtual FSoundEffectSubmixPtr GetEffectSubmix() override;
		virtual USoundSubmix* GetSubmix() override;
		// End of IAudioReverb interface

	private:
		class FStkAudioOutput& StkAudioOutput;
		class FStkSoundSourceManager& StkSoundSourceManager;
		class FStkListenerManager& StkListenerManager;

		FSoundEffectSubmixPtr SubmixEffect;
		TWeakObjectPtr<USoundSubmix> ReverbSubmix;

		FAudioDevice* AudioDevice;
	};
}

class FStkSubmixEffectReverbPlugin : public FSoundEffectSubmix
{
public:
	// FSoundEffectSubmix interface
	virtual uint32 GetDesiredInputChannelCountOverride() const override;
	// End of FSoundEffectSubmix interface
};

USTRUCT()
struct FStkSubmixEffectReverbPluginSettings
{
	GENERATED_BODY()
};

UCLASS()
class UStkSubmixEffectReverbPluginPreset : public USoundEffectSubmixPreset
{
	GENERATED_BODY()

public:
	EFFECT_PRESET_METHODS(StkSubmixEffectReverbPlugin)

	UPROPERTY(EditAnywhere, Category = SubmixEffectPreset)
	FStkSubmixEffectReverbPluginSettings Settings;
};
