//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#include "StkOcclusionSourceSettings.h" 
#include "StkCommon.h"
#include "Curves/CurveFloat.h"

UStkOcclusionSourceSettings::UStkOcclusionSourceSettings()
	: bReflectionEnabled(true)
	, bTransmissionEnabled(true)
	, bDiffractionEnabled(true)
{
}
