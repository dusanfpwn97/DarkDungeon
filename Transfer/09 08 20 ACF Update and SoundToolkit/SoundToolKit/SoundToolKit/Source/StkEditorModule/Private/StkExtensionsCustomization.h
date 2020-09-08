//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#pragma once

#include "StkExtensions.h"

#include "IDetailCustomization.h"
#include "Input/Reply.h"

namespace SoundToolKit
{
	/// <summary>
	/// DetailCustomization for StkExtensions actor for displaying buttons such as ShowSoundPaths or ExportAcousticScene.
	/// </summary>
	class FStkExtensionsCustomization : public IDetailCustomization
	{
	public:
		static TSharedRef<IDetailCustomization> MakeInstance();

		// IDetailCustomization interface
		virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;
		// End of IDetailCustomization interface

		TWeakObjectPtr<class AStkExtensions> StkExtensions;
	};
}
