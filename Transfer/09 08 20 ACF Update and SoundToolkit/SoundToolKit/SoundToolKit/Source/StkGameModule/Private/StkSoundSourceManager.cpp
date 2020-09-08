//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#include "StkSoundSourceManager.h"
#include "StkCommon.h"
#include "StkSoundSource.h"
#include "StkOcclusionSourceSettings.h"

namespace SoundToolKit
{
	FStkSoundSourceManager::FStkSoundSourceManager(StkCommandDispatcher& CommandDispatcher, stk::SharedResource<stk::ISoundToolKit> stk)
		: CommandDispatcher(CommandDispatcher)
		, SoundSourcePool(CommandDispatcher, DEFAULT_INITIAL_SOUND_SOURCE_POOL_SIZE, stk)
	{
	}

	FStkSoundSourceManager::~FStkSoundSourceManager() = default;

	void FStkSoundSourceManager::Add(const int32 SourceId, const EAudioPlugin PluginType, void* Settings)
	{
		FScopeLock Lock(&CriticalSection);

		switch (PluginType)
		{
		case EAudioPlugin::SPATIALIZATION:
			return AddSpatialization(SourceId, static_cast<UStkSpatializationSourceSettings*>(Settings));

		case EAudioPlugin::REVERB:
			return AddReverb(SourceId, static_cast<UStkReverbSourceSettings*>(Settings));

		case EAudioPlugin::OCCLUSION:
			return AddOcclusion(SourceId, static_cast<UStkOcclusionSourceSettings*>(Settings));
		}
	}

	void FStkSoundSourceManager::Remove(const int32 SourceId, const EAudioPlugin PluginType)
	{
		FScopeLock Lock(&CriticalSection);

		FStkSoundSource* SoundSource = Get(SourceId);
		if (SoundSource)
		{
			Remove(SourceId);
		}
	}

	void FStkSoundSourceManager::Process(const FAudioPluginSourceInputData& InputData)
	{
		FScopeLock Lock(&CriticalSection);

		FStkSoundSource* SoundSource = Get(InputData.SourceId);
		if (SoundSource)
		{
			STK_LOG(VeryVerbose, TEXT("SoundSourceManager: Processing SoundSource for ID:%d."), InputData.SourceId);

			if (!SoundSource->HasName())
			{
				SoundSource->SetNameFromComponentID(InputData.AudioComponentId);
			}

			SoundSource->SetTransform(
				InputData.SpatializationParams->EmitterWorldPosition,
				InputData.SpatializationParams->EmitterWorldRotation);
			SoundSource->Stream(*InputData.AudioBuffer, InputData.NumChannels);
		}
		else
		{
			STK_LOG(Error, TEXT("Could not find SoundSource with ID %d."), InputData.SourceId);
		}
	}

	void FStkSoundSourceManager::SetSinkId(const int32 InSinkId)
	{
		SinkId = InSinkId;
	}

	int32 FStkSoundSourceManager::GetSinkId() const
	{
		return SinkId;
	}

	int32 FStkSoundSourceManager::Num() const
	{
		return SoundSources.FilterByPredicate([](FStkSoundSource* Source) { return Source != nullptr; }).Num();
	}

	FStkSoundSource* FStkSoundSourceManager::Get(const int32 SourceId)
	{
		if (SourceId >= 0 && SourceId < SoundSources.Num())
		{
			return SoundSources[SourceId];
		}
		else
		{
			return nullptr;
		}
	}

	FStkSoundSourcePool& FStkSoundSourceManager::GetSoundSourcePool()
	{
		return SoundSourcePool;
	}

	void FStkSoundSourceManager::AddOcclusion(const int32 SourceId, UStkOcclusionSourceSettings* Settings)
	{
		STK_LOG(Verbose, TEXT("SoundSourceManager: Adding occlusion to ID:%d."), SourceId);

		FStkSoundSource* SoundSource = nullptr;
		if (Contains(SourceId))
		{
			SoundSource = Get(SourceId);
			if (Settings)
			{
				SoundSource->SetOcclusionProperties(Settings);
			}
		}
		else
		{
			if (Settings)
			{
				auto SettingsInitializer = [Settings](FStkSoundSource& SoundSource)
				{
					SoundSource.SetOcclusionProperties(Settings);
				};
				SoundSource = Add(SourceId, SettingsInitializer);
			}
			else
			{
				SoundSource = Add(SourceId);
			}
		}
	}

	void FStkSoundSourceManager::AddSpatialization(const int32 SourceId, UStkSpatializationSourceSettings* Settings)
	{
		STK_LOG(Verbose, TEXT("SoundSourceManager: Adding spatialization to ID:%d."), SourceId);

		FStkSoundSource* SoundSource = nullptr;
		if (Contains(SourceId))
		{
			SoundSource = Get(SourceId);
			if (Settings)
			{
				SoundSource->SetSpatializationProperties(Settings);
			}
		}
		else
		{
			if (Settings)
			{
				auto SettingsInitializer = [Settings](FStkSoundSource& SoundSource)
				{
					SoundSource.SetSpatializationProperties(Settings);
				};
				SoundSource = Add(SourceId, SettingsInitializer);
			}
			else
			{
				SoundSource = Add(SourceId);
			}
		}
	}

	void FStkSoundSourceManager::AddReverb(const int32 SourceId, UStkReverbSourceSettings* Settings)
	{
		STK_LOG(Verbose, TEXT("SoundSourceManager: Adding reverb to ID:%d."), SourceId);

		FStkSoundSource* SoundSource = nullptr;
		if (Contains(SourceId))
		{
			SoundSource = Get(SourceId);
			if (Settings)
			{
				SoundSource->SetReverbProperties(Settings);
			}
		}
		else
		{
			if (Settings)
			{
				auto SettingsInitializer = [Settings](FStkSoundSource& SoundSource)
				{
					SoundSource.SetReverbProperties(Settings);
				};
				SoundSource = Add(SourceId, SettingsInitializer);
			}
			else
			{
				SoundSource = Add(SourceId);
			}
		}
	}

	FStkSoundSource* FStkSoundSourceManager::Add(const int32 SourceId)
	{
		STK_CHECK(SourceId >= 0, Error, TEXT("Invalid SourceId."));

		if (SourceId >= SoundSources.Num())
		{
			int32 DeltaSize = SourceId - SoundSources.Num() + 1;
			SoundSources.AddZeroed(DeltaSize);
		}

		SoundSources[SourceId] = SoundSourcePool.GetUninitialized();
		return SoundSources[SourceId];
	}

	FStkSoundSource* FStkSoundSourceManager::Add(const int32 SourceId, FStkSoundSourcePool::SoundSourceInitializer Initializer)
	{
		STK_CHECK(SourceId >= 0, Error, TEXT("Invalid SourceId."));

		if (SourceId >= SoundSources.Num())
		{
			int32 DeltaSize = SourceId - SoundSources.Num() + 1;
			SoundSources.AddZeroed(DeltaSize);
		}

		SoundSources[SourceId] = SoundSourcePool.Get(Initializer);
		return SoundSources[SourceId];
	}


	void FStkSoundSourceManager::Remove(const int32 SourceId)
	{
		if (SourceId >= 0 && SourceId < SoundSources.Num())
		{
			STK_LOG(Verbose, TEXT("SoundSourceManager: Removing ID:%d."), SourceId);
			SoundSourcePool.Release(SoundSources[SourceId]);
			SoundSources[SourceId] = nullptr;
		}
		else
		{
			STK_LOG(Verbose, TEXT("SoundSourceManager: Failed to remove ID:%d."), SourceId);
		}
	}

	bool FStkSoundSourceManager::Contains(const int32 SourceId)
	{
		return SourceId >= 0 && SourceId < SoundSources.Num() && SoundSources[SourceId] != nullptr;
	}
}
