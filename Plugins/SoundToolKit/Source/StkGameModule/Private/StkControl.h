//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#pragma once

#include "Windows/WindowsPlatformCompilerPreSetup.h"

THIRD_PARTY_INCLUDES_START
#include <stk/UniqueResource.h>
#include <stk/IConnection.h>
THIRD_PARTY_INCLUDES_END

namespace stk
{
	class IControl;
	class IIndicator;
}

namespace SoundToolKit
{
	class STKGAMEMODULE_API FStkControl
	{
	public:
		using StatusIndicatorAddedEventHandler = TFunction<void(stk::IIndicator&, FString)>;
		using StatusIndicatorRemovedEventHandler = TFunction<void(stk::IIndicator&)>;

		FStkControl(stk::IControl& Control);
		~FStkControl();

		stk::UniqueResource<stk::IConnection> SubscribeStatusIndicatorAdded(StatusIndicatorAddedEventHandler Handler);
		stk::UniqueResource<stk::IConnection> SubscribeStatusIndicatorRemoved(StatusIndicatorRemovedEventHandler Handler);

	private:
		stk::IControl& StkControl;
	};

}
