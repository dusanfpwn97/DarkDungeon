//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#include "StkControl.h"
#include "StkCommon.h"

THIRD_PARTY_INCLUDES_START
#include <stk/IControl.h>
#include <stk/IIndicator.h>
THIRD_PARTY_INCLUDES_END

namespace SoundToolKit
{
	FStkControl::FStkControl(stk::IControl& Control)
		: StkControl(Control)
	{
	}

	FStkControl::~FStkControl() = default;

	stk::UniqueResource<stk::IConnection> FStkControl::SubscribeStatusIndicatorAdded(StatusIndicatorAddedEventHandler Handler)
	{
		return StkControl.connectOnIndicatorAdded([Handler](stk::IIndicator& StatusIndicator, stk::StringView Entry)
		{
			Handler(StatusIndicator, ANSI_TO_TCHAR(Entry.c_str()));
		});
	}

	stk::UniqueResource<stk::IConnection> FStkControl::SubscribeStatusIndicatorRemoved(StatusIndicatorRemovedEventHandler Handler)
	{
		return StkControl.connectOnIndicatorRemoved(Handler);
	}
}
