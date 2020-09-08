//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#include "IDetailCustomization.h"
#include "Input/Reply.h"
#include "StkScene.h"

#pragma once

namespace SoundToolKit
{
	class FStkSceneCustomization : public IDetailCustomization
	{
	public:
		// IDetailCustomization interface
		static TSharedRef<IDetailCustomization> MakeInstance();
		virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;
		// End of IDetailCustomization interface

	private:
		FReply OnGeometrySerialization();
		FReply OnClearGeometrySerialization();
		bool IsButtonClickable() const;

		TWeakObjectPtr<class AStkScene> StkScene;
	};
}
