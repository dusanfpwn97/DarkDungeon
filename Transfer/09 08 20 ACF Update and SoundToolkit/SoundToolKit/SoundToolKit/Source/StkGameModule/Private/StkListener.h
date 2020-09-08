//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#pragma once

#include "IAudioExtensionPlugin.h"

namespace stk
{
	class IReceiver;
}

namespace SoundToolKit
{
	class StkCommandDispatcher;

	/// <summary>
	/// Class to manage position of receiver in STK audio engine.
	/// </summary>
	class FStkListener : public IAudioPluginListener
	{
	public:
		FStkListener(StkCommandDispatcher& CommandDispatcher, stk::IReceiver* Receiver);
		~FStkListener();

		// IAudioPluginListener interface
		virtual void OnListenerUpdated(FAudioDevice* AudioDevice, const int32 ViewportIndex, const FTransform& ListenerTransform, const float InDeltaSeconds) override;
		// End of IAudioPluginListener interface

	private:
		StkCommandDispatcher& CommandDispatcher;

		stk::IReceiver& StkReceiver;
	};
}
