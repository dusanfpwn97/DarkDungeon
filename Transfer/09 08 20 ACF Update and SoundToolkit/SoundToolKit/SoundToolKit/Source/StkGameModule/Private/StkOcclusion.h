//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#pragma once

#include "IAudioExtensionPlugin.h"
#include "Runtime/Launch/Resources/Version.h"

namespace SoundToolKit
{
	class FStkOcclusionFactory : public IAudioOcclusionFactory
	{
	public:
		FStkOcclusionFactory(class FStkAudioOutput& AudioOutput, class FStkSoundSourceManager& SoundSourceManager, class FStkListenerManager& ListenerManager);

		// IAudioPluginFactory interface
		virtual FString GetDisplayName() override;
#if ENGINE_MINOR_VERSION >= 24
		virtual bool SupportsPlatform(const FString& PlatformName) override;
#else
		virtual bool SupportsPlatform(EAudioPlatform Platform) override;
#endif
		// End of IAudioPluginFactory interface

		// IAudioOcclusionFactory interface
		virtual TAudioOcclusionPtr CreateNewOcclusionPlugin(FAudioDevice* OwningDevice) override;
		virtual UClass* GetCustomOcclusionSettingsClass() const override;
		// End of IAudioOcclusionFactory interface

	private:
		class FStkAudioOutput& StkAudioOutput;
		class FStkSoundSourceManager& StkSoundSourceManager;
		class FStkListenerManager& StkListenerManager;
	};

	class FStkAudioOcclusion : public IAudioOcclusion
	{
	public:
		FStkAudioOcclusion(class FStkAudioOutput& AudioOutput, class FStkSoundSourceManager& SoundSourceManager, class FStkListenerManager& ListenerManager);
		~FStkAudioOcclusion();

		// IAudioOcclusion interface
		virtual void Initialize(const FAudioPluginInitializationParams InitializationParams) override;
		virtual void OnInitSource(const uint32 SourceId, const FName& AudioComponentUserId, const uint32 NumChannels, UOcclusionPluginSourceSettingsBase* InSettings) override;
		virtual void OnReleaseSource(const uint32 SourceId) override;
		virtual void ProcessAudio(const FAudioPluginSourceInputData& InputData, FAudioPluginSourceOutputData& OutputData) override;
		// End of IAudioOcclusion interface

	private:
		class FStkAudioOutput& StkAudioOutput;
		class FStkSoundSourceManager& StkSoundSourceManager;
		class FStkListenerManager& StkListenerManager;

		FAudioDevice* AudioDevice;
	};
}
