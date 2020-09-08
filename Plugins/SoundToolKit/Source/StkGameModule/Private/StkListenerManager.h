//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#pragma once

THIRD_PARTY_INCLUDES_START
#include <stk/SharedResource.h>
#include <stk/ISoundToolKit.h>
THIRD_PARTY_INCLUDES_END

#include "IAudioExtensionPlugin.h"

namespace SoundToolKit
{
	class StkCommandDispatcher;

	/// <summary>
	/// Manager for StkListeners.
	/// </summary>
	class FStkListenerManager
	{
	public:
		FStkListenerManager(StkCommandDispatcher& CommandDispatcher, stk::SharedResource<stk::ISoundToolKit> Stk);

		/// <summary>
		/// Checks whether given AudioDevice has a corresponding StkListner.
		/// </summary>
		/// <param name="AudioDevice"></param>
		bool IsAudioDeviceRegistered(FAudioDevice* AudioDevice);

		/// <summary>
		/// Creates a StkListener for specified AudioDevice and registers it to the device.
		/// </summary>
		/// <param name="AudioDevice"></param>
		void RegisterAudioDevice(FAudioDevice* AudioDevice);

		/// <summary>
		/// Unregisters StkListner from specified AudioDevice and disposes it.
		/// </summary>
		/// <param name="AudioDevice"></param>
		void UnregisterAudioDevice(FAudioDevice* AudioDevice);

	private:
		StkCommandDispatcher& CommandDispatcher;

		stk::SharedResource<stk::ISoundToolKit> StkAudio;

		TMap<FAudioDevice*, TAudioPluginListenerPtr> Listeners;
	};
}
