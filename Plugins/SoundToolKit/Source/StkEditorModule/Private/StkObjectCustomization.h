//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#pragma once

#include "IDetailCustomization.h"
#include "DetailLayoutBuilder.h"
#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"
#include "EngineUtils.h"
#include "Widgets/Text/STextBlock.h"

#include "StkScene.h"
#include "StkAcousticData.h"
#include "StkProjectData.h"

namespace SoundToolKit
{
	template<typename ObjectType>
	class FStkObjectCustomization : public IDetailCustomization
	{
	public:
		static TSharedRef<IDetailCustomization> MakeInstance()
		{
			return MakeShareable(new FStkObjectCustomization);
		}

		// IDetailCustomization interface
		virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override
		{
			TArray<UObject*> StkDataForObjectsBeingCustomized;
			TArray<TWeakObjectPtr<UObject>> ObjectsBeingCustomized;
			DetailBuilder.GetObjectsBeingCustomized(ObjectsBeingCustomized);

			if (ObjectsBeingCustomized.Num())
			{
				// Do not include components attached to actors from blueprints, SoundToolKit data is set only from blueprints (not from blueprint instaces)
				for (TWeakObjectPtr<UObject> ObjectBeingCustomized : ObjectsBeingCustomized)
				{
					if (UActorComponent* ActorComponent = Cast<UActorComponent>(ObjectBeingCustomized.Get()))
					{
						EComponentCreationMethod CreationMethod = ActorComponent->CreationMethod;
						if (CreationMethod != EComponentCreationMethod::Instance && CreationMethod != EComponentCreationMethod::Native)
						{
							return;
						}
					}
				}

				if (ObjectsBeingCustomized[0]->HasAnyFlags(RF_ArchetypeObject))
				{
					for (TWeakObjectPtr<UObject> ObjectBeingCustomized : ObjectsBeingCustomized)
					{
						if (ObjectType* ObjectBeingCustomizedPtr = Cast<ObjectType>(ObjectBeingCustomized.Get()))
						{
							UStkProjectData* StkProjectData = UStkProjectData::Get();
							TMap<UObject*, class UStkAcousticData*>& StkArchetypesAcousticData = StkProjectData->StkArchetypesAcousticData;

							if (!StkArchetypesAcousticData.Contains(ObjectBeingCustomizedPtr))
							{
								StkArchetypesAcousticData.Add(ObjectBeingCustomizedPtr, UStkAcousticData::Create(StkProjectData, ObjectBeingCustomizedPtr));
							}

							StkDataForObjectsBeingCustomized.Add(StkArchetypesAcousticData[ObjectBeingCustomizedPtr]);
						}
					}
				}
				else if (UWorld* ObjectWorld = ObjectsBeingCustomized[0]->GetWorld())
				{
					for (TActorIterator<AStkScene> Scene{ ObjectWorld }; Scene; ++Scene)
					{
						for (TWeakObjectPtr<UObject> ObjectBeingCustomized : ObjectsBeingCustomized)
						{
							if (ObjectType* ObjectBeingCustomizedPtr = Cast<ObjectType>(ObjectBeingCustomized.Get()))
							{
								AActor* Actor = Cast<AActor>(ObjectBeingCustomized);
								if (!Actor)
								{
									Actor = Cast<AActor>(ObjectBeingCustomizedPtr->GetOuter());
								}

								if (Actor)
								{
									if (Actor->GetLevel() != Scene->GetLevel())
									{
										continue;
									}

									if (!Scene->StkObjectsAcousticData.Contains(ObjectBeingCustomizedPtr))
									{
										Scene->StkObjectsAcousticData.Add(ObjectBeingCustomizedPtr, UStkAcousticData::Create(*Scene, ObjectBeingCustomizedPtr));
									}

									StkDataForObjectsBeingCustomized.Add(Scene->StkObjectsAcousticData[ObjectBeingCustomizedPtr]);
								}
							}
						}
					}
				}
			}

			IDetailCategoryBuilder& SoundToolKitCategory = DetailBuilder.EditCategory(
				TEXT("SoundToolKit"), FText::FromString(TEXT("SoundToolKit")), ECategoryPriority::Important);

			if (StkDataForObjectsBeingCustomized.Num() == ObjectsBeingCustomized.Num())
			{
				SoundToolKitCategory.AddExternalObjectProperty(StkDataForObjectsBeingCustomized, TEXT("bUseAsAcousticMesh"));
				SoundToolKitCategory.AddExternalObjectProperty(StkDataForObjectsBeingCustomized, TEXT("AcousticModel"));
				SoundToolKitCategory.AddExternalObjectProperty(StkDataForObjectsBeingCustomized, TEXT("AcousticMesh"));
				SoundToolKitCategory.AddExternalObjectProperty(StkDataForObjectsBeingCustomized, TEXT("AcousticMaterials"));
			}
			else
			{
				SoundToolKitCategory.AddCustomRow(FText::FromString(TEXT("Note")))
					.WholeRowContent()
					[
						SNew(STextBlock)
						.Text(FText::FromString(FString(TEXT("Place one actor of type ")) + *AStkScene::StaticClass()->GetName()
							+ TEXT(" on level that owns the selected object to be able to use SoundToolKit options.")))
						.Font(IDetailLayoutBuilder::GetDetailFont())
						.AutoWrapText(true)
					];
			}
		}
		// End of IDetailCustomization interface
	};
}