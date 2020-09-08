//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#pragma once

#include "IDetailCustomization.h"
#include "DetailLayoutBuilder.h"
#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"
#include "Widgets/Text/STextBlock.h"

namespace SoundToolKit
{
	class FStkProjectDataCustomization : public IDetailCustomization
	{
	public:
		static TSharedRef<IDetailCustomization> MakeInstance()
		{
			return MakeShareable(new FStkProjectDataCustomization);
		}

		// IDetailCustomization interface
		virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override
		{
			DetailBuilder.EditCategory(TEXT("SoundToolKit Project Settings"))
				.AddCustomRow(FText::FromString(TEXT("SoundToolKit Project Settings")))
				.WholeRowContent()
				[
					SNew(STextBlock)
					.Text(FText::FromString(TEXT("This is SoundToolKit plugin auto-generated project file. "
						"Deleting this asset may cause plugin malfunction.")))
					.Font(IDetailLayoutBuilder::GetDetailFont())
					.AutoWrapText(true)
				];
		}
		// End of IDetailCustomization interface
	};
}