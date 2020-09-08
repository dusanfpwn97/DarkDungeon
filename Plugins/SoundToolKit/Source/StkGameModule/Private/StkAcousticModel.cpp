//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#include "StkAcousticModel.h"

#include "StkScene.h"
#include "StkAcousticData.h"

#include "Landscape.h"
#include "Components/StaticMeshComponent.h"
#include "EditorSupportDelegates.h"
#include "EngineUtils.h"

#if WITH_EDITOR
void UStkAcousticModel::Add(UObject* Object)
{
	if (ALandscape* Landscape = Cast<ALandscape>(Object))
	{
		Landscapes.Add(Landscape);
	}
	else if (UStaticMeshComponent* StaticMeshComponent = Cast<UStaticMeshComponent>(Object))
	{
		StaticMeshComponents.Add(StaticMeshComponent);
	}
}

void UStkAcousticModel::Remove(UObject* Object)
{
	if (ALandscape* Landscape = Cast<ALandscape>(Object))
	{
		Landscapes.Remove(Landscape);
	}
	else if (UStaticMeshComponent* StaticMeshComponent = Cast<UStaticMeshComponent>(Object))
	{
		StaticMeshComponents.Remove(StaticMeshComponent);
	}
}

bool UStkAcousticModel::Contains(UObject* Object)
{
	if (ALandscape* Landscape = Cast<ALandscape>(Object))
	{
		return Landscapes.Contains(Landscape);
	}
	else if (UStaticMeshComponent* StaticMeshComponent = Cast<UStaticMeshComponent>(Object))
	{
		return StaticMeshComponents.Contains(StaticMeshComponent);
	}
	
	return false;
}

void UStkAcousticModel::PostLoad()
{
	Super::PostLoad();

	FEditorSupportDelegates::PrepareToCleanseEditorObject.AddLambda([this](UObject* Object)
	{
		if (UWorld* World = Object->GetWorld())
		{
			Landscapes.RemoveAll([World](ALandscape* Landscape)
			{
				return Landscape ? Landscape->GetWorld() == World : true;
			});

			StaticMeshComponents.RemoveAll([World](UStaticMeshComponent* StaticMeshComponent)
			{
				return StaticMeshComponent ? StaticMeshComponent->GetWorld() == World : true;
			});
		}
	});
}
#endif
