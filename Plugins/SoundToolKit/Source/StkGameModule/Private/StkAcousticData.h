//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#pragma once

#include "GameFramework/Actor.h"

#include "StkAcousticModel.h"
#include "StkAcousticMaterial.h"

#include "StkAcousticData.generated.h"

UCLASS(ClassGroup = (SoundToolKit))
class STKGAMEMODULE_API UStkAcousticData : public UObject
{
	GENERATED_BODY()

public:
	static UStkAcousticData* Create(UObject* Outer, UObject* Object);

#if WITH_EDITOR
public:
	void SetObject(UObject* InObject);
#endif

public:
	/// Whether or not use this object as acoustic mesh inside SoundToolKit engine.
	UPROPERTY(EditAnywhere, Category = "SoundToolKit")
	bool bUseAsAcousticMesh;

	/// Model is an abstraction of a group of acoustic meshes (StaticMesh & Landscape actors marked to be used as acoustic meshes).
	/// StaticMeshComponents' and Landscapes' meshes with the same StkAcousticModel assigned are loaded and unloaded as one entity into the SoundToolKit engine.
	/// 
	/// All actors without StkAcousticModel specified (None) are grouped as single default model inside SoundToolKit.
	UPROPERTY(EditAnywhere, Category = "SoundToolKit", meta = (EditCondition = "bUseAsAcousticMesh"))
	UStkAcousticModel* AcousticModel;

	/// A static mesh used as a simplified acoustic geometry representation for this object inside SoundToolKit engine.
	/// If no acoustic mesh is selected (None) and 'Use as Acoustic Mesh' is checked, this object's collision mesh is used as acoustic geometry inside SoundToolKit engine.
	UPROPERTY(EditAnywhere, Category = "SoundToolKit", meta = (EditCondition = "bUseAsAcousticMesh"))
	class UStaticMesh* AcousticMesh;

	/// Acoustic material associated with the acoustic mesh for this object per segment.
	/// If no acoustic material is selected (None) and 'Use as Acoustic Mesh' is checked, SoundToolKit's default material is used.
	UPROPERTY(EditAnywhere, Category = "SoundToolKit", meta = (EditCondition = "bUseAsAcousticMesh"))
	TArray<class UStkAcousticMaterial*> AcousticMaterials;

#if WITH_EDITOR
	// UObject interface
	virtual void PostLoad() override;
	virtual bool CanEditChange(const FProperty* InProperty) const override;
	// End of UObjectInterface

	// AActor interface
	virtual void PreEditChange(class FProperty* PropertyAboutToChange) override;
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
	// End of AActor interface
#endif

private:
	UStkAcousticData() = default;

private:
	void UpdateNumberOfAcousticMaterialSlots();

#if WITH_EDITOR
private:
	static class AStkScene* MainScene;
#endif

	UPROPERTY()
	UObject* Object;
};
