//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#include "StkOcclusion.h"
#include "StkCommon.h"
#include "StkListenerManager.h"
#include "StkOcclusionSourceSettings.h"
#include "StkSoundSourceManager.h"

namespace SoundToolKit
{
	FStkOcclusionFactory::FStkOcclusionFactory(FStkAudioOutput& AudioOutput, FStkSoundSourceManager& SoundSourceManager, FStkListenerManager& ListenerManager)
		: StkAudioOutput(AudioOutput)
		, StkSoundSourceManager(SoundSourceManager)
		, StkListenerManager(ListenerManager)
	{
	}

	FString FStkOcclusionFactory::GetDisplayName()
	{
		static FString DisplayName = FString(TEXT("SoundToolKit"));

		return DisplayName;
	}

#if ENGINE_MINOR_VERSION >= 24
	bool FStkOcclusionFactory::SupportsPlatform(const FString& PlatformName)
	{
		return PlatformName == FString(TEXT("Windows"));
	}
#else
	bool FStkOcclusionFactory::SupportsPlatform(EAudioPlatform Platform)
	{
		return Platform == EAudioPlatform::Windows;
	}
#endif

	TAudioOcclusionPtr FStkOcclusionFactory::CreateNewOcclusionPlugin(FAudioDevice* OwningDevice)
	{
		return TAudioOcclusionPtr(new FStkAudioOcclusion(StkAudioOutput, StkSoundSourceManager, StkListenerManager));
	}

	UClass* FStkOcclusionFactory::GetCustomOcclusionSettingsClass() const
	{
		return UStkOcclusionSourceSettings::StaticClass();
	}

	FStkAudioOcclusion::FStkAudioOcclusion(FStkAudioOutput& AudioOutput, FStkSoundSourceManager& SoundSourceManager, FStkListenerManager& ListenerManager)
		: StkAudioOutput(AudioOutput)
		, StkSoundSourceManager(SoundSourceManager)
		, StkListenerManager(ListenerManager)
		, AudioDevice(nullptr)
	{
	}

	FStkAudioOcclusion::~FStkAudioOcclusion()
	{
		StkListenerManager.UnregisterAudioDevice(AudioDevice);
	}

	void FStkAudioOcclusion::Initialize(const FAudioPluginInitializationParams InitializationParams)
	{
		AudioDevice = InitializationParams.AudioDevicePtr;
		StkListenerManager.RegisterAudioDevice(AudioDevice);
	}

	void FStkAudioOcclusion::OnInitSource(const uint32 SourceId, const FName& AudioComponentUserId, const uint32 NumChannels, UOcclusionPluginSourceSettingsBase* InSettings)
	{
		StkSoundSourceManager.Add(SourceId, EAudioPlugin::OCCLUSION, InSettings);
	}
	void FStkAudioOcclusion::OnReleaseSource(const uint32 SourceId)
	{
		StkSoundSourceManager.Remove(SourceId, EAudioPlugin::OCCLUSION);
	}

	void FStkAudioOcclusion::ProcessAudio(const FAudioPluginSourceInputData& InputData, FAudioPluginSourceOutputData& OutputData)
	{
		StkSoundSourceManager.Process(InputData);
	}
}
