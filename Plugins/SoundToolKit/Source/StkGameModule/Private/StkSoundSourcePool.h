//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#pragma once

#include "StkSoundSource.h"

THIRD_PARTY_INCLUDES_START
#include <stk/ISampleStreaming.h>
#include <stk/ISourceSpatial.h>
THIRD_PARTY_INCLUDES_END

#include "Containers/Queue.h"

namespace stk
{
	class ISoundToolKit;
	class ISourceSpatial;
	class ISampleStreaming;
}

namespace SoundToolKit
{
	class StkCommandDispatcher;

	/// <summary>
	/// StkSoundSource object pool used to reduce internal sound source object creation time.
	/// </summary>
	class STKGAMEMODULE_API FStkSoundSourcePool
	{
	public:
		using SoundSourceInitializer = TFunction<void(FStkSoundSource&)>;

		FStkSoundSourcePool(StkCommandDispatcher& CommandDispatcher, const int32 InitialSize, stk::SharedResource<stk::ISoundToolKit> stk);
	
		FStkSoundSource* Get(SoundSourceInitializer Initializer);
		FStkSoundSource* GetUninitialized();

		void Release(FStkSoundSource* SoundSource);

	private:
		struct SoundSourceNativeResources
		{
			stk::SharedResource<stk::ISourceSpatial> SoundSource{ nullptr };
			stk::SharedResource<stk::ISampleStreaming> Sample{ nullptr };
		};

		SoundSourceNativeResources AcquireResources();

		StkCommandDispatcher& CommandDispatcher;

		stk::SharedResource<stk::ISoundToolKit> StkAudio;

		TArray<TUniquePtr<FStkSoundSource>> SpatialPool;

		TQueue<FStkSoundSource*> AvailableSources;
	};
}
