//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#pragma once

#include "IAudioExtensionPlugin.h"
#include "Runtime/Launch/Resources/Version.h"

namespace SoundToolKit
{
	class FStkSpatializationFactory : public IAudioSpatializationFactory
	{
	public:
		FStkSpatializationFactory(class FStkAudioOutput& AudioOutput, class FStkSoundSourceManager& SoundSourceManager, class FStkListenerManager& ListenerManager);

		// IAudioPluginFactory interface
		virtual FString GetDisplayName() override;
#if ENGINE_MINOR_VERSION >= 24
		virtual bool SupportsPlatform(const FString& PlatformName) override;
#else
		virtual bool SupportsPlatform(EAudioPlatform Platform) override;
#endif
		// End of IAudioPluginFactory interface

		// IAudioSpatializationFactory interface
		virtual TAudioSpatializationPtr CreateNewSpatializationPlugin(FAudioDevice* OwningDevice) override;
		virtual UClass* GetCustomSpatializationSettingsClass() const override;
		// End of IAudioSpatializationFactory interface

	private:
		class FStkAudioOutput& StkAudioOutput;
		class FStkSoundSourceManager& StkSoundSourceManager;
		class FStkListenerManager& StkListenerManager;
	};

	class FStkAudioSpatialization : public IAudioSpatialization
	{
	public:
		FStkAudioSpatialization(class FStkAudioOutput& AudioOutput, class FStkSoundSourceManager& SoundSourceManager, class FStkListenerManager& ListenerManager);
		~FStkAudioSpatialization();

		// IAudioSpatialization interface
		virtual void OnInitSource(const uint32 SourceId, const FName& AudioComponentUserId, USpatializationPluginSourceSettingsBase* InSettings) override;
		virtual void OnReleaseSource(const uint32 SourceId) override;
		virtual bool IsSpatializationEffectInitialized() const override;
		virtual void Initialize(const FAudioPluginInitializationParams InitializationParams);
		/// <remarks>
		/// Streams samples for each Sound Source and leaves theirs output silent, apart from
		/// last of the processed sound sources, which has it's output filled with samples rendered by STK.
		/// </remarks>
		virtual void ProcessAudio(const FAudioPluginSourceInputData& InputData, FAudioPluginSourceOutputData& OutputData) override;
		// End of IAudioSpatialization interface

	private:
		class FStkAudioOutput& StkAudioOutput;
		class FStkSoundSourceManager& StkSoundSourceManager;
		class FStkListenerManager& StkListenerManager;

		bool bIsInitialized;
		FAudioDevice* AudioDevice;
	};
}
