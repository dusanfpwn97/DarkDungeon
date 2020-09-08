//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#include "StkSpatialization.h"
#include "StkCommon.h"
#include "StkAudioOutput.h"
#include "StkSoundSourceManager.h"
#include "StkSoundSource.h"
#include "StkListenerManager.h"
#include "StkScene.h"
#include "EngineUtils.h"
#include "Engine/World.h"

namespace SoundToolKit
{
	FStkSpatializationFactory::FStkSpatializationFactory(FStkAudioOutput& AudioOutput, FStkSoundSourceManager& SoundSourceManager, FStkListenerManager& ListenerManager)
		: StkAudioOutput(AudioOutput)
		, StkSoundSourceManager(SoundSourceManager)
		, StkListenerManager(ListenerManager)
	{
	}

	FString FStkSpatializationFactory::GetDisplayName()
	{
		static FString DisplayName = FString(TEXT("SoundToolKit"));

		return DisplayName;
	}

#if ENGINE_MINOR_VERSION >= 24
	bool FStkSpatializationFactory::SupportsPlatform(const FString& PlatformName)
	{
		return PlatformName == FString(TEXT("Windows"));
	}
#else
	bool FStkSpatializationFactory::SupportsPlatform(EAudioPlatform Platform)
	{
		return Platform == EAudioPlatform::Windows;
	}
#endif

	TAudioSpatializationPtr FStkSpatializationFactory::CreateNewSpatializationPlugin(FAudioDevice* OwningDevice)
	{
		return TAudioSpatializationPtr(new FStkAudioSpatialization(StkAudioOutput, StkSoundSourceManager, StkListenerManager));
	}

	UClass* FStkSpatializationFactory::GetCustomSpatializationSettingsClass() const
	{
		return UStkSpatializationSourceSettings::StaticClass();
	}

	FStkAudioSpatialization::FStkAudioSpatialization(FStkAudioOutput& AudioOutput, FStkSoundSourceManager& SoundSourceManager, FStkListenerManager& ListenerManager)
		: StkAudioOutput(AudioOutput)
		, StkSoundSourceManager(SoundSourceManager)
		, StkListenerManager(ListenerManager)
		, bIsInitialized(false)
		, AudioDevice(nullptr)
	{
	}

	FStkAudioSpatialization::~FStkAudioSpatialization()
	{
		StkListenerManager.UnregisterAudioDevice(AudioDevice);
	}

	void FStkAudioSpatialization::OnInitSource(const uint32 SourceId, const FName& AudioComponentUserId, USpatializationPluginSourceSettingsBase* InSettings)
	{
		if (AudioComponentUserId.Compare(Utils::GetAudioSinkName()) == 0)
		{
			StkSoundSourceManager.SetSinkId(SourceId);
		}
		else
		{
			StkSoundSourceManager.Add(SourceId, EAudioPlugin::SPATIALIZATION, InSettings);
		}
	}

	void FStkAudioSpatialization::OnReleaseSource(const uint32 SourceId)
	{
		StkSoundSourceManager.Remove(SourceId, EAudioPlugin::SPATIALIZATION);
	}

	void FStkAudioSpatialization::ProcessAudio(const FAudioPluginSourceInputData& InputData, FAudioPluginSourceOutputData& OutputData)
	{
		if (StkSoundSourceManager.GetSinkId() == InputData.SourceId)
		{
			StkAudioOutput.RenderInto(OutputData.AudioBuffer);
		}
	}

	bool FStkAudioSpatialization::IsSpatializationEffectInitialized() const
	{
		return bIsInitialized;
	}

	void FStkAudioSpatialization::Initialize(const FAudioPluginInitializationParams InitializationParams)
	{
		if (GWorld && GWorld->WorldType == EWorldType::PIE)
		{
			STK_CHECK(TActorIterator<AStkScene>{GWorld}, Error, TEXT("No actor of type '%s' on the scene."), *AStkScene::StaticClass()->GetFName().ToString());
		}

		AudioDevice = InitializationParams.AudioDevicePtr;
		StkListenerManager.RegisterAudioDevice(AudioDevice);

		StkAudioOutput.Prepare(2, InitializationParams.SampleRate, InitializationParams.BufferLength);

		bIsInitialized = true;
	}
}
