//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#pragma once

#include "StkSoundSourcePool.h"
#include "StkOcclusionSourceSettings.h"
#include "StkSpatializationSourceSettings.h"
#include "StkReverbSourceSettings.h"

#include "IAudioExtensionPlugin.h"

namespace stk
{
	class ISoundToolKit;
}

namespace SoundToolKit
{
	class StkCommandDispatcher;

	/// <summary>
	/// Manager for StkSoundSource objects.
	/// </summary>
	class STKGAMEMODULE_API FStkSoundSourceManager
	{
		constexpr static int32 DEFAULT_INITIAL_SOUND_SOURCE_POOL_SIZE = 32;

	public:
		FStkSoundSourceManager(StkCommandDispatcher& CommandDispatcher, stk::SharedResource<stk::ISoundToolKit> stk);
		~FStkSoundSourceManager();

		void Add(const int32 SourceId, const EAudioPlugin PluginType, void* Settings);
		void Remove(const int32 SourceId, const EAudioPlugin PluginType);
		void Process(const FAudioPluginSourceInputData& InputData);
		void SetSinkId(const int32 InSinkId);
		int32 GetSinkId() const;

		int32 Num() const;
		class FStkSoundSource* Get(const int32 SourceId);

		FStkSoundSourcePool& GetSoundSourcePool();

	private:
		void AddOcclusion(const int32 SourceId, UStkOcclusionSourceSettings* Settings);
		void AddSpatialization(const int32 SourceId, UStkSpatializationSourceSettings* Settings);
		void AddReverb(const int32 SourceId, UStkReverbSourceSettings* Settings);

		FStkSoundSource* Add(const int32 SourceId);
		FStkSoundSource* Add(const int32 SourceId, FStkSoundSourcePool::SoundSourceInitializer Initializer);
		void Remove(const int32 SourceId);
		bool Contains(const int32 SourceId);

		StkCommandDispatcher& CommandDispatcher;

		FStkSoundSourcePool SoundSourcePool;
		TArray<FStkSoundSource*> SoundSources;
		int32 SinkId;
		FCriticalSection CriticalSection;
	};
}
