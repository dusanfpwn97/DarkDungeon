//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#include "StkMaterial.h"
#include "StkCommon.h"

THIRD_PARTY_INCLUDES_START
#include <stk/IMaterial.h>
THIRD_PARTY_INCLUDES_END

namespace SoundToolKit
{
	FStkMaterial::FStkMaterial(stk::SharedResource<stk::IMaterial> Material)
		: StkMaterial(Material)
	{
	}

	FStkMaterial::~FStkMaterial() = default;

	stk::SharedResource<stk::IMaterial> FStkMaterial::Native() const
	{
		return StkMaterial;
	}
}
