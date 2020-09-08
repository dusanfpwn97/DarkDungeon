//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#pragma once

#include "Windows/WindowsPlatformCompilerPreSetup.h"

THIRD_PARTY_INCLUDES_START
#pragma warning(disable:4310)
#include <stk/SharedResource.h>
#include <stk/IModel.h>
#pragma warning(default:4310)
THIRD_PARTY_INCLUDES_END

#include "StkMesh.h"
#include "StkGeometryComponent.h"
#include "StkEffectCoefficients.h"

#include "GameFramework/Actor.h"

#include "StkScene.generated.h"

class ALandscape;

class UStkGeometryComponent;
class UStkAcousticModel;
class UStkAcousticData;

namespace SoundToolKit
{
	class FStkGameModule;

	class FStkModelInternalData
	{
	public:
		TArray<SoundToolKit::FStkMesh*> GetMeshes() const;
		bool IsEmpty() const;

	public:
		stk::SharedResource<stk::IModel> Native{ nullptr };
		TMap<UObject*, TArray<TUniquePtr<SoundToolKit::FStkMesh>>> Meshes;

		bool bIsAddedToScene{ false };
		bool bIsRestored{ false };
		bool bIsModified{ false };
	};
}

UCLASS()
class UStkModelSerializationData : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TArray<uint8> Data;

	UPROPERTY()
	TArray<UObject*> OrderedInstances;

	UPROPERTY()
	TArray<UObject*> OrderedArchetypes;
};

/// An actor needed by SoundToolKit engine for internal purposes. There must be exactly one actor of this type on every level.
UCLASS(HideCategories = (Actor, Advanced, Input, Rendering, Replication, Collision, LOD, Cooking, Transform))
class STKGAMEMODULE_API AStkScene : public AActor
{
	GENERATED_BODY()

public:
	using SceneGeometryChangedCallback = TFunction<void()>;

public:
	AStkScene();

	void NotifyGeometryComponentInitialized(UStkGeometryComponent* GeometryComponent);
	void NotifyGeometryComponentUninitialized(UStkGeometryComponent* GeometryComponent);
	void ConnectOnSceneGeometryChanged(SceneGeometryChangedCallback Callback);

	// UObject interface
#if WITH_EDITOR
	virtual void PreEditUndo() override;
	virtual void PostEditUndo() override;
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual bool CanEditChange(const FProperty* InProperty) const override;
#endif
	virtual void PostLoad() override;
	// End of UObject interface

	// AActor interface
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void BeginDestroy() override;
	virtual void PostActorCreated() override;
	// End of AActor interface

	/// Total volume of all sound played by SoundToolKit.
	UPROPERTY(EditAnywhere, Category = "Volume", meta = (ClampMin = "0.0", ClampMax = "4.0", UIMin = "0.0", UIMax = "4.0", DisplayName = "Master"))
	float MasterVolume;

	/// Volume of spatialized sound played by SoundToolKit.
	UPROPERTY(EditAnywhere, Category = "Volume", meta = (ClampMin = "0.0", ClampMax = "4.0", UIMin = "0.0", UIMax = "4.0", DisplayName = "Spatial"))
	float SpatialVolume;

	/// Volume of reverberation sound played by SoundToolKit.
	UPROPERTY(EditAnywhere, Category = "Volume", meta = (ClampMin = "0.0", ClampMax = "4.0", UIMin = "0.0", UIMax = "4.0", DisplayName = "Reverb"))
	float ReverbVolume;

	/// Enables HRTF spatialization.
	UPROPERTY(EditAnywhere, Category = "Spatial Effects")
	bool bEnableHRTF;

	/// Enables attenuation of sound with distance.
	UPROPERTY(EditAnywhere, Category = "Spatial Effects")
	bool bEnableAttenuation;

	/// Enables specular reflection of sound from obstacles.
	UPROPERTY(EditAnywhere, Category = "Occlusion Effects")
	bool bEnableReflection;

	/// Enables transmission of sound through obstacles.
	UPROPERTY(EditAnywhere, Category = "Occlusion Effects")
	bool bEnableTransmission;

	/// Enables diffraction of sound on edges.
	UPROPERTY(EditAnywhere, Category = "Occlusion Effects")
	bool bEnableDiffraction;

	/// The speed of sound in a given acoustic medium [m/s].
	UPROPERTY(EditAnywhere, Category = "Acoustic Medium", meta = (ClampMin = "100", ClampMax = "1000", UIMin = "100", UIMax = "1000"))
	float SpeedOfSound;

	/// Enables attenuation due to acoustic medium viscosity.
	UPROPERTY(EditAnywhere, Category = "Acoustic Medium")
	bool bEnableDamping;

	/// Attenuation due to medium viscosity effect in 8 octave bands.
	UPROPERTY(EditAnywhere, Category = "Acoustic Medium", meta = (EditCondition = "bEnableDamping"))
	FStkEffectCoefficients Damping;

	UPROPERTY()
	TMap<UObject*, class UStkAcousticData*> StkObjectsAcousticData;

	bool IsPersistentLevelActor() const;

	bool IsModelSerialized(UStkAcousticModel* Model) const;

#if WITH_EDITOR
	void SerializeAcousticScene();
	void ClearSerializationData();
#endif

private:
	void CreateAudioSink();

	void FillOrderedInstancesList();
	void FillOrderedArchetypesList();

	TArray<UStkGeometryComponent*> AttachGeometryComponentsToStaticMeshes();
	TArray<UStkGeometryComponent*> AttachGeometryComponentsToArchetypeInstances();
	TArray<UStkGeometryComponent*> AttachGeometryComponentsToArchetypes();

	void PrepareMeshesForComponent(UStkGeometryComponent* GeometryComponent);
	void PrepareMeshesForLandscape(ALandscape* Landscape);
	void PrepareModels();

	void LoadGeometryComponent(UStkGeometryComponent* GeometryComponent);
	void UnloadGeometryComponent(UStkGeometryComponent* GeometryComponent);
	void LoadLandscapes();
	void UnloadLandscapes();

	void ClearScene();

	UStaticMeshComponent* FindStaticMeshComponent(UStkGeometryComponent* GeometryComponent);

#if WITH_EDITOR
	void AddAcousticObjectsToModels();
	void ClearAcousticObjectsRemovedFromScene();
#endif

	void OnMeshesAddedToModel(SoundToolKit::FStkModelInternalData& ModelData);
	void OnMeshesRemovedFromModel(SoundToolKit::FStkModelInternalData& ModelData);

private:
	void OnUpdateVolumes();
	void OnUpdateVolumes(const FName& PropertyName);

	void OnUpdateReflection();
	void OnUpdateDiffraction();
	void OnUpdateTransmission();
	void OnUpdateOcclusionEffects();
	void OnUpdateOcclusionEffects(const FName& PropertyName);

	void OnUpdateHRTF();
	void OnUpdateAttenuation();
	void OnUpdateSpatialEffects();
	void OnUpdateSpatialEffects(const FName& PropertyName);

	void OnUpdateSpeedOfSound();
	void OnUpdateDamping();
	void OnUpdateDampingCoefficients();
	void OnUpdateAcousticMedium();
	void OnUpdateAcousticMedium(const FName& PropertyName, const FName& MemberPropertyName);

private:
	static AStkScene* MainScene;

private:
	TArray<TFunction<void()>> OnDestroyDelegates;

private:
	/// <summary>
	/// Handle to FStkGameModule for frequent Flush() calls.
	/// </summary>
	SoundToolKit::FStkGameModule* StkGameModule;

	/// <summary>
	/// Responsible for outputting audio from SoundToolKit for all sources on the scene.
	/// </summary>
	class UAudioComponent* AudioSink;

	/// <summary>
	/// Fired when acoustic scene changes (when StkGeometryComponent is created on/removed from scene).
	/// </summary>
	SceneGeometryChangedCallback OnSceneGeometryChanged;

	/// <summary>
	/// Data for all models on the scene.
	/// Null acoustic model represents the default model.
	/// </summary>
	TMap<TPair<UStkAcousticModel*, ULevel*>, SoundToolKit::FStkModelInternalData> Models;

	/// <summary>
	/// Serialization data for models from this level.
	/// </summary>
	UPROPERTY()
	TMap<UStkAcousticModel*, UStkModelSerializationData*> SerializationData;

	/// Indicates whether the acoustic scene geometry is serialized.
	UPROPERTY()
	bool bIsAcousticSceneSerialized;

private:
	TArray<UStkGeometryComponent*> CreatedComponentsForInstances;

private:
	TMap<UObject*, class UStkAcousticData*> PreUndoStkObjectsAcousticData;

private:
	friend class UStkBlueprintFunctionLibrary;
};
