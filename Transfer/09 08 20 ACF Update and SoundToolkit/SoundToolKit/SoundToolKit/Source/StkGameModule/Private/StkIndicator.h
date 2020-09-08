//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#pragma once

THIRD_PARTY_INCLUDES_START
#include <stk/UniqueResource.h>
#include <stk/IConnection.h>
THIRD_PARTY_INCLUDES_END

namespace stk
{
	class IIndicator;
}

namespace SoundToolKit
{
	class STKGAMEMODULE_API FStkStatusIndicator
	{
	public:
		FStkStatusIndicator(stk::IIndicator& StatusIndicator);
		~FStkStatusIndicator();

		FString Name() const;
		FString ShortName() const;
		FString Type() const;
		FString Description() const;
		FString Value() const;

		const stk::IIndicator& Native() const;

	private:
		FString CurrentValue;

		stk::IIndicator& StkStatusIndicator;
		stk::UniqueResource<stk::IConnection> ValueChangedSubscription{ nullptr };
	};
}
