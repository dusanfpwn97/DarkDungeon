//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#include "StkExtensionsCustomization.h"
#include "StkCommon.h"
#include "StkExtensions.h"

#include "DesktopPlatformModule.h"
#include "DetailLayoutBuilder.h"
#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Text/STextBlock.h"
#include "Engine/World.h"

#define LOCTEXT_NAMESPACE "SoundToolKitExtensionsNS"

namespace SoundToolKit
{
	TSharedRef<IDetailCustomization> FStkExtensionsCustomization::MakeInstance()
	{
		return MakeShareable(new FStkExtensionsCustomization);
	}

	void FStkExtensionsCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
	{
		const TArray<TWeakObjectPtr<UObject>>& SelectedObjects = DetailBuilder.GetSelectedObjects();
		for (const TWeakObjectPtr<UObject>& Object : SelectedObjects)
		{
			if (Object.IsValid())
			{
				AStkExtensions* StkExtensionsPtr = Cast<AStkExtensions>(Object.Get());
				if (StkExtensionsPtr)
				{
					StkExtensions = StkExtensionsPtr;
					break;
				}
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
