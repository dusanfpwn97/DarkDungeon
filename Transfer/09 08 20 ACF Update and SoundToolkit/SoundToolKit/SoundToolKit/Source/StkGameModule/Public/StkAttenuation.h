//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#pragma once

#include "StkAttenuation.generated.h"

UENUM()
enum class EStkAttenuationFunction : uint8
{
	StkAttenuation_Nothing UMETA(DisplayName = "Nothing"),
	StkAttenuation_Linear UMETA(DisplayName = "Linear"),
	StkAttenuation_Inverse UMETA(DisplayName = "Inverse"),
	StkAttenuation_Logarithmic UMETA(DisplayName = "Logarithmic"),
	StkAttenuation_LineSource UMETA(DisplayName = "Line Source"),
	StkAttenuation_PointSource UMETA(DisplayName = "Point Source"),
	StkAttenuation_ReverseLog UMETA(DisplayName = "Reverse Logarithm"),
	StkAttenuation_Custom UMETA(DisplayName = "Custom")
};
