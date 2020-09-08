//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#pragma once

#include "StkMesh.h"

#include "Components/SceneComponent.h"

#include "StkGeometryComponent.generated.h"

class UStkAcousticData;
class AStkScene;

/// <summary>
/// A component used to tag static meshes so that they become a part of acoustic geometry of the scene.
/// </summary>
UCLASS(ClassGroup = (SoundToolKit), meta = (BlueprintSpawnableComponent),
	HideCategories = (Cooking, Collision, Rendering, Tags, Activation, Physics, LOD, AssetUserData))
class STKGAMEMODULE_API UStkGeometryComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	using StaticMeshLoadedEventHandler = TFunction<void(void)>;

public:
	static UStkGeometryComponent* Create(UStaticMeshComponent* Outer, UStkAcousticData* AcousticData);

public:
	// AActor interface
	virtual void InitializeComponent() override;
	virtual void UninitializeComponent() override;
	virtual bool CanAttachAsChild(USceneComponent* ChildComponent, FName SocketName) const override;
	// End of AActor interface

	TSoftObjectPtr<UStkAcousticData>& GetAcousticData();
	TSoftObjectPtr<UStaticMeshComponent>& GetOuterStaticMeshComponent();

private:
	UStkGeometryComponent();

private:
	UPROPERTY()
	TSoftObjectPtr<UStkAcousticData> AcousticData;

	UPROPERTY()
	TSoftObjectPtr<UStaticMeshComponent> OuterStaticMeshComponent;

private:
	class UStkAcousticModel* PreUndoAcousticModel;
};
