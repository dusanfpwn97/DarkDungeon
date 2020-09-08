//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#include "StkGeometryComponent.h"
#include "StkCommon.h"
#include "StkAcousticMaterial.h"
#include "StkAcousticModel.h"
#include "StkGameModule.h"
#include "StkScene.h"
#include "StkMeshUtils.h"
#include "StkAcousticData.h"

#include <vector>
THIRD_PARTY_INCLUDES_START
#include <stk/Math.h>
#include <stk_ex/utility/MeshFaceValidator.h>
THIRD_PARTY_INCLUDES_END

#include "Engine/StaticMesh.h"
#include "EngineUtils.h"

UStkGeometryComponent* UStkGeometryComponent::Create(UStaticMeshComponent* Outer, UStkAcousticData* AcousticData)
{
	UStkGeometryComponent* NewGeometryCompenent = NewObject<UStkGeometryComponent>(Outer);
	NewGeometryCompenent->AcousticData = AcousticData;
	NewGeometryCompenent->OuterStaticMeshComponent = Outer;
	return NewGeometryCompenent;
}

UStkGeometryComponent::UStkGeometryComponent()
{
	Mobility = EComponentMobility::Static;
	bWantsInitializeComponent = true;

	PrimaryComponentTick.bCanEverTick = false;
}

void UStkGeometryComponent::InitializeComponent()
{
	Super::InitializeComponent();

	if (UWorld* World = GetWorld())
	{
		if (AcousticData && AcousticData->bUseAsAcousticMesh)
		{
			for (TActorIterator<AStkScene> Scene{ World }; Scene; ++Scene)
			{
				if (AActor* RootActor = Cast<AActor>(GetAttachmentRootActor()))
				{
					if (RootActor->GetLevel() != Scene->GetLevel())
					{
						continue;
					}

					Scene->NotifyGeometryComponentInitialized(this);
				}
			}
		}
	}
}

void UStkGeometryComponent::UninitializeComponent()
{
	if (AcousticData && AcousticData->bUseAsAcousticMesh)
	{
		if (UWorld* World = GetWorld())
		{
			for (TActorIterator<AStkScene> Scene{ World }; Scene; ++Scene)
			{
				if (AActor* RootActor = Cast<AActor>(GetAttachmentRootActor()))
				{
					if (RootActor->GetLevel() != Scene->GetLevel())
					{
						continue;
					}

					Scene->NotifyGeometryComponentUninitialized(this);
				}
			}
		}
	}

	Super::UninitializeComponent();
}

bool UStkGeometryComponent::CanAttachAsChild(USceneComponent* ChildComponent, FName SocketName) const
{
	return false;
}

TSoftObjectPtr<UStkAcousticData>& UStkGeometryComponent::GetAcousticData()
{
	return AcousticData;
}

TSoftObjectPtr<UStaticMeshComponent>& UStkGeometryComponent::GetOuterStaticMeshComponent()
{
	return OuterStaticMeshComponent;
}
