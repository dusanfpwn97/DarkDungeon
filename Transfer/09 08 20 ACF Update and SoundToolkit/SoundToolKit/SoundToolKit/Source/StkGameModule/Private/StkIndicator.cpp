//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#include "StkIndicator.h"
#include "StkCommon.h"

THIRD_PARTY_INCLUDES_START
#include <stk/IIndicator.h>
THIRD_PARTY_INCLUDES_END

namespace
{
	FString TypeName(stk::IndicatorType type)
	{
		switch (type)
		{
		case stk::IndicatorType::Boolean:
			return "Boolean";
		case stk::IndicatorType::UInt64:
			return "UInt64";
		case stk::IndicatorType::Float:
			return "Float";
		case stk::IndicatorType::String:
			return "String";
		default:
			return "InvalidType";
		}
	}
}

namespace SoundToolKit
{
	FStkStatusIndicator::FStkStatusIndicator(stk::IIndicator& StatusIndicator)
		: StkStatusIndicator(StatusIndicator)
	{
		ValueChangedSubscription = StkStatusIndicator.connectOnValueChanged([&Value{ CurrentValue }](stk::IIndicator&, stk::StringView NewValue)
		{
			Value = ANSI_TO_TCHAR(NewValue.c_str());
		});
	}

	FStkStatusIndicator::~FStkStatusIndicator()
	{
		if (ValueChangedSubscription)
		{
			ValueChangedSubscription->disconnect();
		}
	}

	FString FStkStatusIndicator::Name() const
	{
		return ANSI_TO_TCHAR(StkStatusIndicator.name().c_str());
	}

	FString FStkStatusIndicator::ShortName() const
	{
		return SoundToolKit::Utils::ShortName(StkStatusIndicator.name());
	}

	FString FStkStatusIndicator::Type() const
	{
		return TypeName(StkStatusIndicator.type());
	}

	FString FStkStatusIndicator::Description() const
	{
		return ANSI_TO_TCHAR(StkStatusIndicator.description().c_str());
	}

	FString FStkStatusIndicator::Value() const
	{
		return CurrentValue;
	}

	const stk::IIndicator& FStkStatusIndicator::Native() const
	{
		return StkStatusIndicator;
	}
}
