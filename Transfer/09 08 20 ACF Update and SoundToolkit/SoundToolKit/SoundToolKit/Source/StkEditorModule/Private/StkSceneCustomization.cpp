//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#include "StkSceneCustomization.h"
#include "DetailLayoutBuilder.h"
#include "Widgets/Input/SButton.h"
#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"
#include "Widgets/Text/STextBlock.h"

#define LOCTEXT_NAMESPACE "StkSceneCustomization"

namespace SoundToolKit
{
	TSharedRef<IDetailCustomization> FStkSceneCustomization::MakeInstance()
	{
		return MakeShareable(new FStkSceneCustomization);
	}

	void FStkSceneCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
	{
		const TArray<TWeakObjectPtr<UObject>>& SelectedObjects = DetailBuilder.GetSelectedObjects();
		for (const TWeakObjectPtr<UObject>& Object : SelectedObjects)
		{
			if (Object.IsValid())
			{
				AStkScene* StkScenePtr = Cast<AStkScene>(Object.Get());
				if (StkScenePtr)
				{
					StkScene = StkScenePtr;
					break;
				}
			}
		}

		IDetailCategoryBuilder& AcousticSceneCategory = DetailBuilder.EditCategory("Acoustic Scene Serialization");

		FDetailWidgetRow& AcousticSceneSerializationRow = AcousticSceneCategory.AddCustomRow(
			LOCTEXT("AcousticSceneSerialization", "Acoustic Scene Serialization"));

		AcousticSceneSerializationRow
			.NameContent()
			[
				SNullWidget::NullWidget
			]
			.ValueContent()
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SButton)
					.ContentPadding(3)
					.VAlign(VAlign_Center)
					.HAlign(HAlign_Center)
					.OnClicked(this, &FStkSceneCustomization::OnGeometrySerialization)
					[
						SNew(STextBlock)
						.Text(LOCTEXT("AcousticSceneSerialization", "Serialize Acoustic Scene"))
						.Font(IDetailLayoutBuilder::GetDetailFont())
					]
					.ToolTipText(LOCTEXT("SerializationTooltip", "Serializes the acoustic geometry of the scene (including all sublevels). "
						"If acoustic geometry remains unmodified, acoustic scene will be restored upon next scene load."
						"\nRestoration of a serialized geometry takes much less time than geometry creation."
						"\nAvailable only in Editor mode."))
				]
			]
			.IsEnabled(TAttribute<bool>(this, &FStkSceneCustomization::IsButtonClickable));

			FDetailWidgetRow& AcousticSceneClearSerializationRow = AcousticSceneCategory.AddCustomRow(
				LOCTEXT("AcousticSceneClearSerialization", "Acoustic Scene Serialization"));

		AcousticSceneClearSerializationRow
			.NameContent()
			[
				SNullWidget::NullWidget
			]
			.ValueContent()
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SButton)
					.ContentPadding(3)
					.VAlign(VAlign_Center)
					.HAlign(HAlign_Center)
					.OnClicked(this, &FStkSceneCustomization::OnClearGeometrySerialization)
					[
						SNew(STextBlock)
						.Text(LOCTEXT("ClearAcousticSceneSerialization", "Clear Serialization Data"))
						.Font(IDetailLayoutBuilder::GetDetailFont())
					]
					.ToolTipText(LOCTEXT("ClearSerializationTooltip", "Deletes all serialized data of the scene. If acoustic meshes are not serialized, "
						"its' geometry is created at runtime from scratch which might be much slower comparing to restoring previously saved data."
						"\nAvailable only in Editor mode."))
				]
			]
			.IsEnabled(TAttribute<bool>(this, &FStkSceneCustomization::IsButtonClickable));
	}

	FReply FStkSceneCustomization::OnGeometrySerialization()
	{
		if (StkScene.IsValid())
		{
			StkScene->SerializeAcousticScene();
		}

		return FReply::Handled();
	}

	FReply FStkSceneCustomization::OnClearGeometrySerialization()
	{
		if (StkScene.IsValid())
		{
			StkScene->ClearSerializationData();
		}

		return FReply::Handled();
	}

	bool FStkSceneCustomization::IsButtonClickable() const
	{
		return !StkScene->HasActorBegunPlay() && StkScene->IsPersistentLevelActor();
	}
}

#undef LOCTEXT_NAMESPACE
