//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#include "StkListenerManager.h"
#include "StkCommon.h"
#include "StkCommandDispatcher.h"
#include "StkListener.h"

THIRD_PARTY_INCLUDES_START
#include <stk/IScene.h>
#include <stk/IReceiver.h>
THIRD_PARTY_INCLUDES_END

#include "AudioDevice.h"

namespace SoundToolKit
{
	FStkListenerManager::FStkListenerManager(StkCommandDispatcher& CommandDispatcher, stk::SharedResource<stk::ISoundToolKit> Stk)
		: CommandDispatcher(CommandDispatcher)
		, StkAudio(Stk)
	{
	}

	bool FStkListenerManager::IsAudioDeviceRegistered(FAudioDevice* AudioDevice)
	{
		return Listeners.Contains(AudioDevice);
	}

	void FStkListenerManager::RegisterAudioDevice(FAudioDevice* AudioDevice)
	{
		if (!IsAudioDeviceRegistered(AudioDevice))
		{
			stk::IReceiver* ReceiverPtr = &StkAudio->scene().receiver();
			TAudioPluginListenerPtr& Listner = Listeners.Emplace(AudioDevice, TAudioPluginListenerPtr(new FStkListener(CommandDispatcher, ReceiverPtr)));
			AudioDevice->RegisterPluginListener(Listner);
		}
	}

	void FStkListenerManager::UnregisterAudioDevice(FAudioDevice* AudioDevice)
	{
		if (IsAudioDeviceRegistered(AudioDevice))
		{
			AudioDevice->UnregisterPluginListener(Listeners[AudioDevice]);
			Listeners.Remove(AudioDevice);
		}
	}
}
