//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#include "StkSoundSourcePool.h"
#include "StkCommon.h"
#include "StkCommandDispatcher.h"

THIRD_PARTY_INCLUDES_START
#include <stk/ISoundToolKit.h>
#include <stk/IResourcesFactory.h>
THIRD_PARTY_INCLUDES_END

#include "CoreGlobals.h"

namespace SoundToolKit
{
	FStkSoundSourcePool::FStkSoundSourcePool(StkCommandDispatcher& CommandDispatcher, const int32 InitialSize, stk::SharedResource<stk::ISoundToolKit> stk)
		: CommandDispatcher(CommandDispatcher)
		, StkAudio(stk)
	{
		TArray<SoundSourceNativeResources> SoundSourceNativeResources;

		CommandDispatcher.Execute([InitialSize, &stk, &SoundSourceNativeResources]()
		{
			for (int32 i = 0; i < InitialSize; ++i)
			{
				SoundSourceNativeResources.Add({ stk->resourcesFactory().createSpatialSoundSource(), stk->resourcesFactory().createSampleStreaming() });
			}
		});

		SpatialPool.Reserve(InitialSize);
		for (int32 i = 0; i < InitialSize; ++i)
		{
			int32 SpatialIndex = SpatialPool.Emplace(MakeUnique<FStkSoundSource>(
				CommandDispatcher, stk, SoundSourceNativeResources[i].SoundSource, SoundSourceNativeResources[i].Sample));
			AvailableSources.Enqueue(SpatialPool[SpatialIndex].Get());
		}
	}

	FStkSoundSource* FStkSoundSourcePool::Get(SoundSourceInitializer Initializer)
	{
		FStkSoundSource* SoundSource = GetUninitialized();
		Initializer(*SoundSource);

		return SoundSource;
	}

	FStkSoundSource* FStkSoundSourcePool::GetUninitialized()
	{
		FStkSoundSource* SoundSource = nullptr;

		if (!AvailableSources.Dequeue(SoundSource))
		{
			SoundSourceNativeResources Resources = AcquireResources();
			int32 Index = SpatialPool.Emplace(MakeUnique<FStkSoundSource>(CommandDispatcher, StkAudio, Resources.SoundSource, Resources.Sample));
			SoundSource = SpatialPool[Index].Get();
		}

		SoundSource->ResumePlayback();
		return SoundSource;
	}

	void FStkSoundSourcePool::Release(FStkSoundSource* SoundSource)
	{
		SoundSource->Reset();
		AvailableSources.Enqueue(SoundSource);
	}

	FStkSoundSourcePool::SoundSourceNativeResources FStkSoundSourcePool::AcquireResources()
	{
		SoundSourceNativeResources Resources;

		CommandDispatcher.Execute([&Audio{ StkAudio }, &Resources]()
		{
			Resources.SoundSource = Audio->resourcesFactory().createSpatialSoundSource();
			Resources.Sample = Audio->resourcesFactory().createSampleStreaming();
		});

		return Resources;
	}
}
