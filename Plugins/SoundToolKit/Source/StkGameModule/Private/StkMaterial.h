//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#pragma once

THIRD_PARTY_INCLUDES_START
#include <stk/SharedResource.h>
#include <stk/IMaterial.h>
THIRD_PARTY_INCLUDES_END

namespace SoundToolKit
{
	/// <summary>
	/// Manages a Material within SoundToolKit engine.
	/// </summary>
	class FStkMaterial
	{
	public:
		FStkMaterial(stk::SharedResource<stk::IMaterial> Material);
		~FStkMaterial();

		stk::SharedResource<stk::IMaterial> Native() const;

	private:
		stk::SharedResource<stk::IMaterial> StkMaterial;
	};
}
