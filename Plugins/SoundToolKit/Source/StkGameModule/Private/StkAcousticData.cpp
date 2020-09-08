//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#include "StkAcousticData.h"
#include "StkGeometryComponent.h"
#include "StkScene.h"

#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "UObject/UObjectIterator.h"

#if WITH_EDITOR
AStkScene* UStkAcousticData::MainScene;
#endif

UStkAcousticData* UStkAcousticData::Create(UObject* Outer, UObject* Object)
{
	UStkAcousticData* NewAcousticData = NewObject<UStkAcousticData>(Outer);
	NewAcousticData->Object = Object;

#if WITH_EDITOR
	NewAcousticData->UpdateNumberOfAcousticMaterialSlots();
#endif

	return NewAcousticData;
}

#if WITH_EDITOR
void UStkAcousticData::SetObject(UObject* InObject)
{
	Object = InObject;
}

void UStkAcousticData::PostLoad()
{
	Super::PostLoad();

	for (TObjectIterator<AStkScene> Scene; Scene; ++Scene)
	{
		if (Scene->GetWorld()->WorldType == EWorldType::Editor)
		{
			if (Scene->IsPersistentLevelActor())
			{
				MainScene = *Scene;
				return;
			}
		}
	}
}

bool UStkAcousticData::CanEditChange(const FProperty* InProperty) const
{
	bool bBaseEditable = Super::CanEditChange(InProperty);

	return bBaseEditable && (GetWorld() ? GetWorld()->WorldType == EWorldType::Editor : Object->HasAnyFlags(RF_ArchetypeObject));
}

void UStkAcousticData::PreEditChange(FProperty* PropertyAboutToChange)
{
	if (PropertyAboutToChange)
	{
		const FName& PropertyName = PropertyAboutToChange->GetFName();
		if (AcousticModel && PropertyName == GET_MEMBER_NAME_CHECKED(UStkAcousticData, AcousticModel))
		{
			AcousticModel->Remove(Object);
		}
		else if (AcousticModel && PropertyName == GET_MEMBER_NAME_CHECKED(UStkAcousticData, bUseAsAcousticMesh))
		{
			if (bUseAsAcousticMesh)
			{
				AcousticModel->Remove(Object);
			}
			else if (!AcousticModel->Contains(Object))
			{
				AcousticModel->Add(Object);
			}
		}
	}

	if (MainScene)
	{
		MainScene->ClearSerializationData();
	}

	Super::PreEditChange(PropertyAboutToChange);
}

void UStkAcousticData::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	const FName& PropertyName = PropertyChangedEvent.GetPropertyName();
	if (AcousticModel && PropertyName.IsEqual(GET_MEMBER_NAME_CHECKED(UStkAcousticData, AcousticModel)))
	{
		AcousticModel->Add(Object);
	}
	else if (PropertyName.IsEqual(GET_MEMBER_NAME_CHECKED(UStkAcousticData, AcousticMesh)))
	{
		UpdateNumberOfAcousticMaterialSlots();
	}

	Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif

void UStkAcousticData::UpdateNumberOfAcousticMaterialSlots()
{
	int32 NumberOfAcousticMaterialSlots;
	if (AcousticMesh)
	{
		NumberOfAcousticMaterialSlots = AcousticMesh->GetNumSections(0);
	}
	else if (UStaticMeshComponent* StaticMeshComponent = Cast<UStaticMeshComponent>(Object))
	{
		UStaticMesh* StaticMesh = StaticMeshComponent->GetStaticMesh();
		NumberOfAcousticMaterialSlots = StaticMesh ? StaticMesh->GetNumSections(StaticMesh->LODForCollision) : 0;
	}
	else
	{
		NumberOfAcousticMaterialSlots = 1;
	}

	AcousticMaterials.SetNumZeroed(NumberOfAcousticMaterialSlots);
}
