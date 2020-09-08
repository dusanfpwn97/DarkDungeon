//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#include "StkListener.h"
#include "StkCommon.h"
#include "StkGameModule.h"

THIRD_PARTY_INCLUDES_START
#include <stk/IReceiver.h>
#include <stk/Math.h>
THIRD_PARTY_INCLUDES_END

#include "AudioDevice.h"
#include "AudioDeviceManager.h"

namespace SoundToolKit
{
	FStkListener::FStkListener(StkCommandDispatcher& CommandDispatcher, stk::IReceiver* Receiver)
		: CommandDispatcher(CommandDispatcher)
		, StkReceiver(*Receiver)
	{
	}

	FStkListener::~FStkListener() = default;

	void FStkListener::OnListenerUpdated(FAudioDevice* AudioDevice, const int32 ViewportIndex, const FTransform& ListenerTransform, const float InDeltaSeconds)
	{
		if (AudioDevice == FAudioDevice::GetAudioDeviceManager()->GetActiveAudioDevice().GetAudioDevice())
		{
			stk::vec3 Position = Utils::ConvertVector(ListenerTransform.GetLocation());
			stk::quaternion Rotation = Utils::ConvertQuaternion(ListenerTransform.GetRotation());

			CommandDispatcher.Enqueue([&StkReceiver{ StkReceiver }, Position, Rotation]
				{
					StkReceiver.setTransform(Position, Rotation);
				});
		}
	}
}
