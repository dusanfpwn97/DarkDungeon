//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#include "StkCommon.h"
#include "StkSpatializationSourceSettings.h"

UStkSpatializationSourceSettings::UStkSpatializationSourceSettings()
	: Attenuation(EStkAttenuationFunction::StkAttenuation_PointSource)
	, InnerRadius(25.0f)
	, FallofDistance(30000.f)
	, bUseHrtfSpatialization(true)
{
}
