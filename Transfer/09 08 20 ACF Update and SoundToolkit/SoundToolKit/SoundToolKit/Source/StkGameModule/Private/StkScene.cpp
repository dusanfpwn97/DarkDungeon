//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#include "StkScene.h"
#include "StkCommon.h"
#include "StkAcousticModel.h"
#include "StkAcousticMaterial.h"
#include "StkMesh.h"
#include "StkGameModule.h"
#include "StkMaterialAssetsGenerator.h"
#include "StkGeometryComponent.h"
#include "StkAcousticData.h"
#include "StkProjectData.h"
#include "StkMeshUtils.h"

THIRD_PARTY_INCLUDES_START
#include <stk/Math.h>
#include <stk/IScene.h>
#include <stk/IAcousticMedium.h>
#include <stk_ex/utility/MeshFaceValidator.h>
THIRD_PARTY_INCLUDES_END

#include "Runtime/Launch/Resources/Version.h"
#include "Model.h"
#include "Landscape.h"
#include "Engine/StaticMeshActor.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundWaveProcedural.h"
#include "EngineUtils.h"
#include "Engine/StaticMesh.h"
#include "Engine/BlueprintGeneratedClass.h"
#include "Engine/SimpleConstructionScript.h"
#include "Engine/SCS_Node.h"
#include "Components/InstancedStaticMeshComponent.h"

#if WITH_EDITOR
#include "Editor.h"
#include "PropertyEditorModule.h"
#include "ScopedTransaction.h"
#include "Misc/ScopedSlowTask.h"
#endif

namespace
{
	TArray<stk::SharedResource<stk::IMesh>> ToNativeMeshes(const TArray<SoundToolKit::FStkMesh*> Meshes)
	{
		TArray<stk::SharedResource<stk::IMesh>> StkMeshes;
		for (SoundToolKit::FStkMesh* Mesh : Meshes)
		{
			StkMeshes.Add(Mesh->Native());
		}
		return StkMeshes;
	}

	void SetModelMeshes(stk::SharedResource<stk::IModel> Model, const TArray<SoundToolKit::FStkMesh*>& Meshes)
	{
		TArray<stk::SharedResource<stk::IMesh>> NativeMeshes = ToNativeMeshes(Meshes);
		Model->setMeshes(stk::ArrayView<stk::SharedResource<stk::IMesh>>{
			NativeMeshes.GetData(), static_cast<size_t>(NativeMeshes.Num())});
	}

	TArray<SoundToolKit::FStkMesh*> ToRawPointerMeshes(const TArray<TUniquePtr<SoundToolKit::FStkMesh>>& Meshes)
	{
		TArray<SoundToolKit::FStkMesh*> MeshesPtrs;
		MeshesPtrs.Reserve(Meshes.Num());
		for (const TUniquePtr<SoundToolKit::FStkMesh>& Mesh : Meshes)
		{
			MeshesPtrs.Add(Mesh.Get());
		}
		return MeshesPtrs;
	}
}

namespace SoundToolKit
{
	TArray<SoundToolKit::FStkMesh*> FStkModelInternalData::GetMeshes() const
	{
		TArray<SoundToolKit::FStkMesh*> ModelMeshes;
		for (auto& ObjectMeshes : Meshes)
		{
			ModelMeshes.Append(ToRawPointerMeshes(ObjectMeshes.Value));
		}
		return ModelMeshes;
	}

	bool FStkModelInternalData::IsEmpty() const
	{
		return !GetMeshes().Num();
	}
}

AStkScene* AStkScene::MainScene;

AStkScene::AStkScene()
	: MasterVolume(1.0f)
	, SpatialVolume(1.0f)
	, ReverbVolume(1.0f)
	, bEnableHRTF(true)
	, bEnableAttenuation(true)
	, bEnableReflection(true)
	, bEnableTransmission(true)
	, bEnableDiffraction(true)
	, SpeedOfSound(343.f)
	, bEnableDamping(false)
	// Default values of Damping correnspond to air, temperature: 15 degrees Celsius, pressure: 1013 hPa, humidity: 30%.
	, Damping(4.99651760e-05f, 0.000116024588f, 0.000379357982f, 0.00142597477f, 0.00550973462f, 0.0203645360f, 0.0633036569f, 0.137860075f)
	, StkGameModule(&SoundToolKit::Utils::GetGameModule())
	, bIsAcousticSceneSerialized(false)
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.SetTickFunctionEnable(true);
	PrimaryActorTick.bStartWithTickEnabled = true;

#if WITH_EDITOR
	bLockLocation = true;
#endif

	CreateAudioSink();
}

void AStkScene::ConnectOnSceneGeometryChanged(SceneGeometryChangedCallback Callback)
{
	OnSceneGeometryChanged = Callback;
}

void AStkScene::NotifyGeometryComponentInitialized(UStkGeometryComponent* GeometryComponent)
{
	if (HasActorBegunPlay())
	{
		TPair<UStkAcousticModel*, ULevel*> ModelKey{ GeometryComponent->GetAcousticData()->AcousticModel, GetLevel() };
		bool bShouldCreateNewModel = !MainScene->Models.Contains(ModelKey);

		SoundToolKit::FStkModelInternalData& ModelData = MainScene->Models.FindOrAdd(ModelKey);
		ModelData.bIsModified = true;

		if (bShouldCreateNewModel)
		{
			ModelData.Native = StkGameModule->CreateModel({});
		}

		LoadGeometryComponent(GeometryComponent);
	}
}

void AStkScene::NotifyGeometryComponentUninitialized(UStkGeometryComponent* GeometryComponent)
{
	if (HasActorBegunPlay())
	{
		if (UWorld* World = GetWorld())
		{
			if (!World->bIsTearingDown)
			{
				TPair<UStkAcousticModel*, ULevel*> ModelKey{ GeometryComponent->GetAcousticData()->AcousticModel, GetLevel() };

				SoundToolKit::FStkModelInternalData& ModelData = MainScene->Models[ModelKey];
				ModelData.bIsModified = !GetLevel()->bIsBeingRemoved;

				UnloadGeometryComponent(GeometryComponent);
			}
		}
	}
}

#if WITH_EDITOR
void AStkScene::PreEditUndo()
{
	Super::PreEditUndo();

	StkObjectsAcousticData.Remove(nullptr);
	PreUndoStkObjectsAcousticData = StkObjectsAcousticData;
}

void AStkScene::PostEditUndo()
{
	Super::PostEditUndo();

	for (TPair<UObject*, UStkAcousticData*> StkObjectAcousticData : StkObjectsAcousticData)
	{
		UObject* CurrentObject = StkObjectAcousticData.Key;
		UStkAcousticData* Data = StkObjectAcousticData.Value;
		Data->SetObject(CurrentObject);

		UStkAcousticModel* Model = Data->AcousticModel;
		bool bUseAsAcousticMesh = Data->bUseAsAcousticMesh;

		if (UObject* const* ObjectPtr = PreUndoStkObjectsAcousticData.FindKey(Data))
		{
			UObject* PreUndoObject = *ObjectPtr;
			if (PreUndoObject != CurrentObject)
			{
				if (CurrentObject && Model && bUseAsAcousticMesh)
				{
					if (!Data->AcousticModel->Contains(CurrentObject))
					{
						Data->AcousticModel->Add(CurrentObject);
					}
				}
				else
				{
					Data->AcousticModel->Remove(CurrentObject);
				}
			}
		}
		else
		{
			if (Model && bUseAsAcousticMesh)
			{
				if (!Model->Contains(CurrentObject))
				{
					Data->AcousticModel->Add(CurrentObject);
				}
			}
		}
	}
}

void AStkScene::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	if (PropertyChangedEvent.Property && PropertyChangedEvent.MemberProperty)
	{
		const FName& PropertyName = PropertyChangedEvent.GetPropertyName();
		const FName& MemberPropertyName = PropertyChangedEvent.MemberProperty->GetFName();

		if (StkGameModule)
		{
			OnUpdateVolumes(PropertyName);
			OnUpdateSpatialEffects(PropertyName);
			OnUpdateOcclusionEffects(PropertyName);
			OnUpdateAcousticMedium(PropertyName, MemberPropertyName);
		}
	}

	Super::PostEditChangeProperty(PropertyChangedEvent);
}

bool AStkScene::CanEditChange(const FProperty* InProperty) const
{
	bool bBaseEditable = Super::CanEditChange(InProperty);

	return bBaseEditable && IsPersistentLevelActor();
}
#endif

void AStkScene::PostLoad()
{
#if WITH_EDITOR
	ClearAcousticObjectsRemovedFromScene();
#endif

	Super::PostLoad();

	if (IsPersistentLevelActor())
	{
		MainScene = this;
	}

	if (UWorld* World = GetWorld())
	{
		if (World->WorldType != EWorldType::Editor && World->WorldType != EWorldType::Inactive)
		{
			if (!MainScene->bIsAcousticSceneSerialized)
			{
				FillOrderedInstancesList();
				if (IsPersistentLevelActor())
				{
					FillOrderedArchetypesList();
				}
			}

			CreatedComponentsForInstances = AttachGeometryComponentsToStaticMeshes();
			CreatedComponentsForInstances.Append(AttachGeometryComponentsToArchetypeInstances());
			if (IsPersistentLevelActor())
			{
				AttachGeometryComponentsToArchetypes();
			}
		}
	}

#if WITH_EDITOR
	SoundToolKit::StkMaterialAssetsGenerator::Generate();

	if (UWorld* World = GetWorld())
	{
		if (World->WorldType == EWorldType::Editor || World->WorldType == EWorldType::Inactive)
		{
			AddAcousticObjectsToModels();

			FEditorDelegates::OnDeleteActorsEnd.AddUObject(this, &AStkScene::ClearAcousticObjectsRemovedFromScene);
			FEditorDelegates::PostSaveWorld.AddWeakLambda(this, [this](uint32, UWorld*, bool) { ClearAcousticObjectsRemovedFromScene(); });

			if (IsPersistentLevelActor())
			{
				FEditorDelegates::OnNewActorsDropped.AddWeakLambda(this, [this](const TArray<UObject*>&, const TArray<AActor*>&) { ClearSerializationData(); });
				FEditorDelegates::OnDeleteActorsBegin.AddWeakLambda(this, [this] { ClearSerializationData(); });
				FWorldDelegates::OnPreWorldRename.AddWeakLambda(this, [this](UWorld*, const TCHAR*, UObject*, ERenameFlags, bool&) { ClearSerializationData(); });
			}
		}
	}
#endif
}


void AStkScene::BeginPlay()
{
	StkGameModule->NotifyOnSceneInitialized(this);

	if (UWorld* World = GetWorld())
	{
		if (World->WorldType != EWorldType::Editor && World->WorldType != EWorldType::Inactive)
		{
			if (IsPersistentLevelActor())
			{
				if (!bIsAcousticSceneSerialized)
				{
					STK_LOG(Display, TEXT("Acoustic scene geometry data is not serialized. "
						"Serialize geometry via %s actor from the persistent level for better performance."), *GetName())
				}
				else
				{
					STK_LOG(Display, TEXT("Using serialized acoustic scene data for loading the geometry. "
						"Always make sure the data is up to date and no changes were made to the acoustic scene after serialization."));
				}
			}

			// 1. Prepare meshes for geometry components
			for (auto Component : CreatedComponentsForInstances)
			{
				PrepareMeshesForComponent(Component);
			}

			// 2. Prepare meshes for landscapes
			for (TPair<UStkAcousticModel*, UStkModelSerializationData*> ModelSerializationData : SerializationData)
			{
				for (UObject* Object : ModelSerializationData.Value->OrderedInstances)
				{
					if (ALandscape* Landscape = Cast<ALandscape>(Object))
					{
						UStkAcousticData* AcousticData = StkObjectsAcousticData[Object];
						if (AcousticData->bUseAsAcousticMesh)
						{
							PrepareMeshesForLandscape(Landscape);
						}
					}
				}
			}

			// 3. Create models for meshes
			PrepareModels();

			// 4. Load already created acoustic meshes
			for (auto Component : CreatedComponentsForInstances)
			{
				LoadGeometryComponent(Component);
			}
			LoadLandscapes();
		}
	}

	if (OnSceneGeometryChanged)
	{
		OnSceneGeometryChanged();
	}

	if (IsPersistentLevelActor())
	{
		OnUpdateVolumes();
		OnUpdateSpatialEffects();
		OnUpdateOcclusionEffects();
		OnUpdateAcousticMedium();

		USoundWaveProcedural* AudioSinkWave = NewObject<USoundWaveProcedural>(AudioSink);
		AudioSinkWave->NumChannels = 1;
		AudioSinkWave->bIsBus = true;
		AudioSinkWave->Priority = TNumericLimits<float>::Max();
#if ENGINE_MINOR_VERSION >= 23
		AudioSinkWave->VirtualizationMode = EVirtualizationMode::PlayWhenSilent;
#else
		AudioSinkWave->bVirtualizeWhenSilent = true;
#endif
		AudioSink->SetSound(AudioSinkWave);
		AudioSink->Play();
	}

	Super::BeginPlay();
}

void AStkScene::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UnloadLandscapes();
	ClearScene();

	if (IsPersistentLevelActor())
	{
		StkGameModule->Finish();
	}

	Super::EndPlay(EndPlayReason);
}

void AStkScene::BeginDestroy()
{
	CreatedComponentsForInstances.Empty();

#if WITH_EDITOR
	if (IsPersistentLevelActor())
	{
		FWorldDelegates::OnPreWorldRename.RemoveAll(this);
		FEditorDelegates::OnDeleteActorsBegin.RemoveAll(this);
		FEditorDelegates::OnNewActorsDropped.RemoveAll(this);
	}

	FEditorDelegates::PostSaveWorld.RemoveAll(this);
	FEditorDelegates::OnDeleteActorsEnd.RemoveAll(this);
#endif

	Super::BeginDestroy();
}

void AStkScene::PostActorCreated()
{
	Super::PostActorCreated();

	AudioSink->SetWorldLocation(FVector(0, 0, 0));
}

bool AStkScene::IsPersistentLevelActor() const
{
	return GetLevel() ? GetLevel()->IsPersistentLevel() : false;
}

bool AStkScene::IsModelSerialized(UStkAcousticModel* Model) const
{
	return SerializationData.Contains(Model) && SerializationData[Model]->Data.Num();
}

#if WITH_EDITOR
void AStkScene::SerializeAcousticScene()
{
	const FScopedTransaction Transaction(FText::FromString(TEXT("SerializeAcousticScene")));
	// 1. Clear serialization data
	ClearSerializationData();

	for (TObjectIterator<AStkScene> Scene; Scene; ++Scene)
	{
		if (Scene->GetWorld()->WorldType == EWorldType::Editor)
		{
			Scene->Modify();
		}
	}

	// 2. Create models & meshes inside SoundToolKit
	TArray<UStkGeometryComponent*> CreatedGeometryComponentsForArchetypes;
	for (TObjectIterator<AStkScene> Scene; Scene; ++Scene)
	{
		if (Scene->GetWorld()->WorldType == EWorldType::Editor)
		{
			if (Scene->IsPersistentLevelActor())
			{
				MainScene = this;

				Scene->FillOrderedArchetypesList();
			}

			Scene->FillOrderedInstancesList();

			Scene->CreatedComponentsForInstances = Scene->AttachGeometryComponentsToStaticMeshes();
			Scene->CreatedComponentsForInstances.Append(Scene->AttachGeometryComponentsToArchetypeInstances());
			if (Scene->IsPersistentLevelActor())
			{
				CreatedGeometryComponentsForArchetypes.Append(Scene->AttachGeometryComponentsToArchetypes());
			}
		}
	}

	for (TObjectIterator<AStkScene> Scene; Scene; ++Scene)
	{
		if (Scene->GetWorld()->WorldType == EWorldType::Editor)
		{
			// Initialize geometry components
			TArray<UStkGeometryComponent*> InstaceComponents = Scene->CreatedComponentsForInstances;
			if (Scene->IsPersistentLevelActor())
			{
				InstaceComponents.Append(CreatedGeometryComponentsForArchetypes);
			}

			for (UStkGeometryComponent* GeometryComponent : InstaceComponents)
			{
				Scene->OnDestroyDelegates.Add([GeometryComponent]
				{
					GeometryComponent->DestroyComponent();
				});
			}

			// Prepare meshes for geometry components
			for (auto Component : Scene->CreatedComponentsForInstances)
			{
				Scene->PrepareMeshesForComponent(Component);
			}

			// Prepare meshes for landscapes
			for (TPair<UStkAcousticModel*, UStkModelSerializationData*> ModelSerializationData : Scene->SerializationData)
			{
				for (UObject* Object : ModelSerializationData.Value->OrderedInstances)
				{
					if (ALandscape* Landscape = Cast<ALandscape>(Object))
					{
						UStkAcousticData* AcousticData = Scene->StkObjectsAcousticData[Object];
						if (AcousticData->bUseAsAcousticMesh)
						{
							Scene->PrepareMeshesForLandscape(Landscape);
						}
					}
				}
			}

			Scene->PrepareModels();

			// Load already created static meshes
			for (auto Component : Scene->CreatedComponentsForInstances)
			{
				Scene->LoadGeometryComponent(Component);
			}

			// Load already created landscape meshes
			Scene->LoadLandscapes();
		}
	}

	StkGameModule->Finish();

	// 3. Serialize all models
	FScopedSlowTask SlowTask(Models.Num(), FText::FromString(TEXT("Serializing Acoustic Scene")));
	SlowTask.MakeDialog();

	for (auto& Model : Models)
	{
		stk::SharedResource<stk::IModel> NativeModel = Model.Value.Native;
		stk::ArrayView<std::byte> DataArray;
		NativeModel->saveGeometry([&DataArray](stk::ArrayView<std::byte> Data) { DataArray = Data; });
		StkGameModule->Finish();

		for (TObjectIterator<AStkScene> Scene; Scene; ++Scene)
		{
			if (Scene->GetWorld()->WorldType == EWorldType::Editor)
			{
				ULevel* Level = Model.Key.Value;
				if (Scene->GetLevel() == Level)
				{
					UStkAcousticModel* ModelAsset = Model.Key.Key;
					UStkModelSerializationData* ModelSerializationData;
					if (Scene->SerializationData.Contains(ModelAsset))
					{
						ModelSerializationData = Scene->SerializationData[Model.Key.Key];
					}
					else
					{
						ModelSerializationData = Scene->SerializationData.Emplace(ModelAsset, NewObject<UStkModelSerializationData>(*Scene));
					}

					ModelSerializationData->Data.Append(TArray<uint8>(reinterpret_cast<uint8*>(const_cast<std::byte*>(DataArray.data())), static_cast<int32>(DataArray.size())));
				}
			}
		}

		SlowTask.EnterProgressFrame();
	}

	// 4. Clear the scene
	for (TObjectIterator<AStkScene> Scene; Scene; ++Scene)
	{
		if (Scene->GetWorld()->WorldType == EWorldType::Editor)
		{
			Scene->ClearScene();
			Scene->CreatedComponentsForInstances.Empty();
		}
	}

	StkGameModule->Finish();

	bIsAcousticSceneSerialized = true;
}

void AStkScene::ClearSerializationData()
{
	if (bIsAcousticSceneSerialized)
	{
		const FScopedTransaction Transaction(FText::FromString(TEXT("ClearSerializationData")));

		for (TObjectIterator<AStkScene> Scene; Scene; ++Scene)
		{
			if (Scene->GetWorld()->WorldType == EWorldType::Editor)
			{
				Scene->Modify();
			}
		}

		for (TObjectIterator<AStkScene> Scene; Scene; ++Scene)
		{
			if (Scene->GetWorld()->WorldType == EWorldType::Editor)
			{
				Scene->SerializationData.Empty();
			}
		}

		bIsAcousticSceneSerialized = false;
	}
}
#endif

void AStkScene::CreateAudioSink()
{
	AudioSink = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioSink"));
	AudioSink->AudioComponentUserID = SoundToolKit::Utils::GetAudioSinkName();

	AudioSink->bOverrideAttenuation = true;
	AudioSink->AttenuationOverrides.SpatializationAlgorithm = ESoundSpatializationAlgorithm::SPATIALIZATION_HRTF;
	AudioSink->AttenuationOverrides.bEnableReverbSend = false;
	AudioSink->AttenuationOverrides.bEnableOcclusion = false;
	AudioSink->AttenuationOverrides.bAttenuate = false;

#if WITH_EDITOR
	AudioSink->SetMobility(EComponentMobility::Static);
#if ENGINE_MINOR_VERSION >= 24
	AudioSink->SetVisibility(false);
#else
	AudioSink->bVisible = false;
#endif
	AudioSink->bVisualizeComponent = false;
#endif

	SetRootComponent(AudioSink);
}

void AStkScene::FillOrderedInstancesList()
{
	for (TPair<UObject*, UStkAcousticData*> StkObjectAcousticData : StkObjectsAcousticData)
	{
		bool bObjectOwnedByThisScene = false;
		if (UStaticMeshComponent* StaticMeshComponent = Cast<UStaticMeshComponent>(StkObjectAcousticData.Key))
		{
			bObjectOwnedByThisScene = GetLevel() == StaticMeshComponent->GetComponentLevel();
		}
		else if (ALandscape* Landscape = Cast<ALandscape>(StkObjectAcousticData.Key))
		{
			bObjectOwnedByThisScene = GetLevel() == Landscape->GetLevel();
		}

		if (bObjectOwnedByThisScene)
		{
			UStkAcousticModel* AcousticModel = StkObjectAcousticData.Value->AcousticModel;
			if (!SerializationData.Contains(AcousticModel))
			{
				SerializationData.Add(AcousticModel, NewObject<UStkModelSerializationData>(this));
			}

			SerializationData[AcousticModel]->OrderedInstances.Add(StkObjectAcousticData.Key);
		}
	}
}

void AStkScene::FillOrderedArchetypesList()
{
	UStkProjectData* StkProjectData = UStkProjectData::Get();
	for (TPair<UObject*, UStkAcousticData*> StkArchetypesAcousticData : StkProjectData->StkArchetypesAcousticData)
	{
		if (StkArchetypesAcousticData.Key)
		{
			UStkAcousticModel* AcousticModel = StkArchetypesAcousticData.Value->AcousticModel;
			if (!SerializationData.Contains(AcousticModel))
			{
				SerializationData.Add(AcousticModel, NewObject<UStkModelSerializationData>(this));
			}

			SerializationData[AcousticModel]->OrderedArchetypes.Add(StkArchetypesAcousticData.Key);
		}
	}
}

TArray<UStkGeometryComponent*> AStkScene::AttachGeometryComponentsToStaticMeshes()
{
	TArray<UStkGeometryComponent*> CreatedGeometryComponents;

	for (TPair<UStkAcousticModel*, UStkModelSerializationData*> ModelSerializationData : SerializationData)
	{
		for (UObject* Object : ModelSerializationData.Value->OrderedInstances)
		{
			if (UStaticMeshComponent* StaticMeshComponent = Cast<UStaticMeshComponent>(Object))
			{
				UStkAcousticData* AcousticData = StkObjectsAcousticData[Object];
				if (AcousticData->bUseAsAcousticMesh)
				{
					UStkGeometryComponent* StkGeometryComponent = UStkGeometryComponent::Create(StaticMeshComponent, AcousticData);
					StkGeometryComponent->SetupAttachment(StaticMeshComponent);

					CreatedGeometryComponents.Add(StkGeometryComponent);
				}
			}
		}
	}

	return CreatedGeometryComponents;
}

TArray<UStkGeometryComponent*> AStkScene::AttachGeometryComponentsToArchetypeInstances()
{
	TArray<UStkGeometryComponent*> CreatedGeometryComponents;

	for (TPair<UStkAcousticModel*, UStkModelSerializationData*> ModelSerializationData : MainScene->SerializationData)
	{
		for (UObject* Object : ModelSerializationData.Value->OrderedArchetypes)
		{
			TArray<UObject*> ArchetypeInstances;
			Object->GetArchetypeInstances(ArchetypeInstances);
			ArchetypeInstances.Sort([](const UObject& Object1, const UObject& Object2)
			{
				return Object1.GetFullName() < Object2.GetFullName();
			});

			for (UObject* ArchetypeInstance : ArchetypeInstances)
			{
				if (UStaticMeshComponent* StaticMeshComponent = Cast<UStaticMeshComponent>(ArchetypeInstance))
				{
					if (StaticMeshComponent->GetComponentLevel() == GetLevel())
					{
						UStkProjectData* StkProjectData = UStkProjectData::Get();
						UStkAcousticData* AcousticData = StkProjectData->StkArchetypesAcousticData[Object];
						if (AcousticData->bUseAsAcousticMesh)
						{
							UStkGeometryComponent* StkGeometryComponent = UStkGeometryComponent::Create(StaticMeshComponent, AcousticData);
							StkGeometryComponent->SetupAttachment(StaticMeshComponent);

							CreatedGeometryComponents.Add(StkGeometryComponent);
						}
					}
				}
			}
		}
	}

	return CreatedGeometryComponents;
}

TArray<UStkGeometryComponent*> AStkScene::AttachGeometryComponentsToArchetypes()
{
	TArray<UStkGeometryComponent*> CreatedGeometryComponents;

	if (UWorld* World = GetWorld())
	{
		UStkProjectData* StkProjectData = UStkProjectData::Get();
		for (TPair<UObject*, UStkAcousticData*> StkArchetypeAcousticData : StkProjectData->StkArchetypesAcousticData)
		{
			if (UStaticMeshComponent* StaticMeshComponent = Cast<UStaticMeshComponent>(StkArchetypeAcousticData.Key))
			{
				if (StkArchetypeAcousticData.Value->bUseAsAcousticMesh)
				{
					if (StaticMeshComponent->HasAnyFlags(RF_ArchetypeObject))
					{
						if (UObject* Outer = StaticMeshComponent->GetOuter())
						{
							if (UBlueprintGeneratedClass* BlueprintClass = Cast<UBlueprintGeneratedClass>(Outer))
							{
								USCS_Node* Node = NewObject<USCS_Node>(BlueprintClass->SimpleConstructionScript);
								Node->AddToRoot();
								UStkGeometryComponent* GeometryComponent = UStkGeometryComponent::Create(StaticMeshComponent, StkArchetypeAcousticData.Value);
								Node->ComponentTemplate = GeometryComponent;
								BlueprintClass->SimpleConstructionScript->AddNode(Node);

								CreatedGeometryComponents.Add(GeometryComponent);

								OnDestroyDelegates.Add([BlueprintConstructionScript = BlueprintClass->SimpleConstructionScript, Node]
								{
									BlueprintConstructionScript->RemoveNode(Node);
								});
							}
						}
					}
				}
			}
		}
	}

	return CreatedGeometryComponents;
}

void AStkScene::PrepareMeshesForComponent(UStkGeometryComponent* GeometryComponent)
{
	UStkAcousticData* AcousticData = GeometryComponent->GetAcousticData().Get();

	SoundToolKit::FStkModelInternalData& ModelData = MainScene->Models.FindOrAdd(TPair<UStkAcousticModel*, ULevel*>{AcousticData->AcousticModel, GetLevel()});
	UStaticMeshComponent* TargetComponent = FindStaticMeshComponent(GeometryComponent);

	int32 NumberOfInstances = 1;
	if (UInstancedStaticMeshComponent* InstancedComponent = Cast<UInstancedStaticMeshComponent>(TargetComponent))
	{
		NumberOfInstances = InstancedComponent->GetInstanceCount();
	}

	auto& Meshes = ModelData.Meshes.Emplace(GeometryComponent);
	UStaticMesh* AcousticMesh = AcousticData->AcousticMesh ? AcousticData->AcousticMesh : TargetComponent->GetStaticMesh();
	int32 LOD = AcousticData->AcousticMesh ? 0 : AcousticMesh->LODForCollision;
	Meshes.SetNumZeroed(NumberOfInstances * AcousticMesh->GetNumSections(LOD));

	for (int32 i = 0; i < Meshes.Num(); ++i)
	{
		Meshes[i] = SoundToolKit::Utils::GetGameModule().CreateMesh();
	}
}

void AStkScene::PrepareMeshesForLandscape(ALandscape* Landscape)
{
	UStkAcousticData* AcousticData = StkObjectsAcousticData[Landscape];

	SoundToolKit::FStkModelInternalData& ModelData = MainScene->Models.FindOrAdd(TPair<UStkAcousticModel*, ULevel*>{AcousticData->AcousticModel, GetLevel()});
	int32 NumberOfMeshes = 1;
	if (AcousticData->AcousticMesh)
	{
		const FStaticMeshLODResources& RenderData = AcousticData->AcousticMesh->GetLODForExport(0);
		NumberOfMeshes = RenderData.Sections.Num();
	}

	auto& Meshes = ModelData.Meshes.Emplace(Landscape);
	Meshes.SetNumZeroed(NumberOfMeshes);

	for (int32 i = 0; i < Meshes.Num(); ++i)
	{
		Meshes[i] = SoundToolKit::Utils::GetGameModule().CreateMesh();
	}
}

void AStkScene::PrepareModels()
{
	for (auto& ModelData : MainScene->Models)
	{
		if (ModelData.Key.Value == GetLevel())
		{
			ModelData.Value.Native = StkGameModule->CreateModel(ModelData.Value.GetMeshes());
		}
	}
}

void AStkScene::LoadGeometryComponent(UStkGeometryComponent* GeometryComponent)
{
	UStaticMeshComponent* FoundComponent = FindStaticMeshComponent(GeometryComponent);
	if (!FoundComponent)
	{
		STK_LOG(Error, TEXT("StkGeometryComponent is not attached to StaticMeshComponent."));
		return;
	}

	TSoftObjectPtr<UStaticMeshComponent>& OuterStaticMeshComponent = GeometryComponent->GetOuterStaticMeshComponent();
	TSoftObjectPtr<UStkAcousticData>& AcousticData = GeometryComponent->GetAcousticData();

	UStaticMesh* AcousticMesh = AcousticData->AcousticMesh ? AcousticData->AcousticMesh : FoundComponent->GetStaticMesh();
	int32 LOD = AcousticData->AcousticMesh ? 0 : AcousticMesh->LODForCollision;
	int32 NumberOfInstances = 1;
	TArray<FMatrix> LocalToWorldPerInstance{ FoundComponent->GetComponentToWorld().ToMatrixWithScale() };

	if (UInstancedStaticMeshComponent* InstancedComponent = Cast<UInstancedStaticMeshComponent>(FoundComponent))
	{
		NumberOfInstances = InstancedComponent->GetInstanceCount();
		LocalToWorldPerInstance.SetNumZeroed(NumberOfInstances);
		for (int32 i = 0; i < NumberOfInstances; ++i)
		{
			FTransform InstanceTransform;
			InstancedComponent->GetInstanceTransform(i, InstanceTransform, true);
			LocalToWorldPerInstance[i] = InstanceTransform.ToMatrixWithScale();
		}
	}

	SoundToolKit::FStkModelInternalData& ModelData = MainScene->Models[{AcousticData->AcousticModel, GetLevel()}];
	auto& Meshes = ModelData.bIsModified ? ModelData.Meshes.Emplace(GeometryComponent) : ModelData.Meshes[GeometryComponent];

	if (ModelData.bIsModified)
	{
		Meshes.SetNumZeroed(NumberOfInstances * AcousticMesh->GetNumSections(LOD));
		for (int32 i = 0; i < Meshes.Num(); ++i)
		{
			Meshes[i] = SoundToolKit::Utils::GetGameModule().CreateMesh();
		}
	}

	const FStaticMeshLODResources& RenderData = AcousticMesh->GetLODForExport(LOD);
	if (RenderData.Sections.Num() != (Meshes.Num() / NumberOfInstances))
	{
		STK_LOG(Error, TEXT("Meshes and RenderData sections count mismatch in %s."), *GeometryComponent->GetAttachmentRootActor()->GetName());
		return;
	}

	for (int32 i = 0; i < Meshes.Num(); ++i)
	{
		int32 MaterialIndex = i % (Meshes.Num() / NumberOfInstances);
		if (AcousticData->AcousticMaterials.IsValidIndex(MaterialIndex))
		{
			if (UStkAcousticMaterial* AcousticMaterial = AcousticData->AcousticMaterials[MaterialIndex])
			{
				Meshes[i]->SetMaterial(AcousticMaterial->GetMaterial());
			}
		}
	}

	if (!IsModelSerialized(AcousticData->AcousticModel) || ModelData.bIsModified)
	{
		auto setFaces = [&Meshes](UStaticMesh* StaticMesh, int32 LOD, int32 InstanceNumber, const FMatrix& LocalToWorld)
		{
			TArray<TArray<stk::face>> OutMeshSectionFaces;
			SoundToolKit::Utils::GetStaticMeshFacesForLOD(StaticMesh, LOD, LocalToWorld, OutMeshSectionFaces);

			for (int32 SectionIndex = 0; SectionIndex < OutMeshSectionFaces.Num(); ++SectionIndex)
			{
				Meshes[InstanceNumber * OutMeshSectionFaces.Num() + SectionIndex]->SetFaces(MoveTemp(OutMeshSectionFaces[SectionIndex]));
			}
		};

		for (int32 i = 0; i < NumberOfInstances; ++i)
		{
			setFaces(AcousticMesh, LOD, i, LocalToWorldPerInstance[i]);
		}
	}
	else if (!ModelData.bIsRestored)
	{
		TArray<uint8>& Data = SerializationData[AcousticData->AcousticModel]->Data;
		ModelData.Native->restoreGeometry(stk::ArrayView<std::byte>(reinterpret_cast<std::byte*>(Data.GetData()), Data.Num()));

		ModelData.bIsRestored = true;
	}

	OnMeshesAddedToModel(ModelData);
}

void AStkScene::UnloadGeometryComponent(UStkGeometryComponent* GeometryComponent)
{
	SoundToolKit::FStkModelInternalData& ModelData = MainScene->Models[{GeometryComponent->GetAcousticData()->AcousticModel, GetLevel()}];

	if (ModelData.bIsModified)
	{
		ModelData.Meshes.Remove(GeometryComponent);
	}

	OnMeshesRemovedFromModel(ModelData);
}

void AStkScene::LoadLandscapes()
{
	for (TPair<UStkAcousticModel*, UStkModelSerializationData*> ModelSerializationData : SerializationData)
	{
		for (UObject* Object : ModelSerializationData.Value->OrderedInstances)
		{
			if (ALandscape* Landscape = Cast<ALandscape>(Object))
			{
				UStkAcousticData* StkLandscapeData = StkObjectsAcousticData[Object];
				if (StkLandscapeData->bUseAsAcousticMesh)
				{
					SoundToolKit::FStkModelInternalData& ModelData = MainScene->Models[{StkLandscapeData->AcousticModel, GetLevel()}];
					auto& Meshes = ModelData.Meshes[Landscape];

					TArray<TArray<stk::face>> LandscapeMeshFacesPerSection;
					if (!StkLandscapeData->AcousticMesh)
					{
						LandscapeMeshFacesPerSection.AddZeroed();
						SoundToolKit::Utils::GetLandscapeCollisionFaces(Landscape, LandscapeMeshFacesPerSection[0]);
					}
					else
					{
						const FMatrix LocalToWorld = Landscape->ActorToWorld().ToMatrixNoScale();
						SoundToolKit::Utils::GetStaticMeshFacesForLOD(StkLandscapeData->AcousticMesh, 0, LocalToWorld, LandscapeMeshFacesPerSection);
					}

					if (!IsModelSerialized(StkLandscapeData->AcousticModel) || ModelData.bIsModified)
					{
						for (int32 i = 0; i < LandscapeMeshFacesPerSection.Num(); ++i)
						{
							if (StkLandscapeData->AcousticMaterials.IsValidIndex(Meshes.Num()))
							{
								if (UStkAcousticMaterial* AcousticMaterial = StkLandscapeData->AcousticMaterials[Meshes.Num()])
								{
									Meshes[i]->SetMaterial(AcousticMaterial->GetMaterial());
								}
							}

							Meshes[i]->SetFaces(MoveTemp(LandscapeMeshFacesPerSection[i]));
						}
					}
					else if (!ModelData.bIsRestored)
					{
						TArray<uint8>& Data = SerializationData[StkLandscapeData->AcousticModel]->Data;
						ModelData.Native->restoreGeometry(stk::ArrayView<std::byte>(reinterpret_cast<std::byte*>(Data.GetData()), Data.Num()));

						ModelData.bIsRestored = true;
					}

					OnMeshesAddedToModel(ModelData);
				}
			}
		}
	}
}

void AStkScene::UnloadLandscapes()
{
	for (TPair<UStkAcousticModel*, UStkModelSerializationData*> ModelSerializationData : SerializationData)
	{
		for (UObject* Object : ModelSerializationData.Value->OrderedInstances)
		{
			if (ALandscape* Landscape = Cast<ALandscape>(Object))
			{
				UStkAcousticData* StkLandscapeData = StkObjectsAcousticData[Object];
				if (StkLandscapeData->bUseAsAcousticMesh)
				{
					SoundToolKit::FStkModelInternalData& ModelData = MainScene->Models[{StkLandscapeData->AcousticModel, GetLevel()}];
					ModelData.Meshes.Remove(Landscape);
					OnMeshesRemovedFromModel(ModelData);
				}
			}
		}
	}
}

void AStkScene::ClearScene()
{
	if (IsPersistentLevelActor())
	{
		StkGameModule->Clear();
		Models.Empty();
	}
	else
	{
		TArray<TPair<UStkAcousticModel*, ULevel*>> ModelsToRemove;
		for (auto& ModelData : MainScene->Models)
		{
			if (ModelData.Key.Value == GetLevel())
			{
				ModelsToRemove.Add(ModelData.Key);
			}
		}
		for (auto& ModelToRemove : ModelsToRemove)
		{
			SoundToolKit::FStkModelInternalData& ModelData = MainScene->Models[ModelToRemove];
			if (ModelData.bIsAddedToScene)
			{
				StkGameModule->RemoveModel(MainScene->Models[ModelToRemove].Native);
				ModelData.bIsAddedToScene = false;

			}
			MainScene->Models.Remove(ModelToRemove);
		}
	}

	for (auto& Delegate : OnDestroyDelegates)
	{
		Delegate();
	}
	OnDestroyDelegates.Empty();
}

UStaticMeshComponent* AStkScene::FindStaticMeshComponent(UStkGeometryComponent* GeometryComponent)
{
	TSoftObjectPtr<UStaticMeshComponent>& OuterStaticMeshComponent = GeometryComponent->GetOuterStaticMeshComponent();
	TSoftObjectPtr<UStkAcousticData>& AcousticData = GeometryComponent->GetAcousticData();

	AActor* RootActor = GeometryComponent->GetAttachmentRootActor();
	if (!RootActor || !OuterStaticMeshComponent.Get())
	{
		STK_LOG(Error, TEXT("StkGeometryComponent is not properly attached to an actor."));
		return nullptr;
	}

	UStaticMeshComponent* FoundComponent = Cast<UStaticMeshComponent>(GeometryComponent->GetAttachParent());
	if (!FoundComponent)
	{ // Try to find matching component for runtime-generated meshes (from archetypes)
#if ENGINE_MINOR_VERSION >= 24
		TArray<UActorComponent*> Components;
		RootActor->GetComponents(UStaticMeshComponent::StaticClass(), Components);
#else
		TArray<UActorComponent*> Components = RootActor->GetComponentsByClass(UStaticMeshComponent::StaticClass());
#endif
		for (UActorComponent* Component : Components)
		{
			if (UStaticMeshComponent* StaticMeshComponent = Cast<UStaticMeshComponent>(Component))
			{
				if (StaticMeshComponent->IsBasedOnArchetype(OuterStaticMeshComponent.Get()))
				{
					FoundComponent = StaticMeshComponent;
					break;
				}
			}
		}
	}

	return FoundComponent;
}

#if WITH_EDITOR
void AStkScene::AddAcousticObjectsToModels()
{
	if (UWorld* World = GetWorld())
	{
		if (World->WorldType == EWorldType::Editor || World->WorldType == EWorldType::Inactive)
		{
			auto AddAcousticObjectsToModelsImpl = [](TMap<UObject*, UStkAcousticData*>& ObjectsAcousticData)
			{
				TArray<UObject*> ObjectsToRemove;
				for (TPair<UObject*, UStkAcousticData*> StkObjectAcousticData : ObjectsAcousticData)
				{
					bool bShouldBeRemoved = !StkObjectAcousticData.Key || !StkObjectAcousticData.Value ||
						(StkObjectAcousticData.Key->HasAnyFlags(RF_ArchetypeObject) && !StkObjectAcousticData.Key->GetOuter()->IsInBlueprint());

					if (bShouldBeRemoved)
					{
						ObjectsToRemove.Add(StkObjectAcousticData.Key);
						continue;
					}

					UStkAcousticModel* AcousticModel = StkObjectAcousticData.Value->AcousticModel;
					if (StkObjectAcousticData.Value->bUseAsAcousticMesh && AcousticModel)
					{
						if (!AcousticModel->Contains(StkObjectAcousticData.Key))
						{
							AcousticModel->Add(StkObjectAcousticData.Key);
						}
					}
				}
				for (UObject* ObjectToRemove : ObjectsToRemove)
				{
					ObjectsAcousticData.Remove(ObjectToRemove);
				}
			};

			AddAcousticObjectsToModelsImpl(StkObjectsAcousticData);
			if (IsPersistentLevelActor())
			{
				if (UStkProjectData* ProjectData = UStkProjectData::Get())
				{
					AddAcousticObjectsToModelsImpl(ProjectData->StkArchetypesAcousticData);
				}
			}
		}
	}
}

void AStkScene::ClearAcousticObjectsRemovedFromScene()
{
	if (!IsActorBeingDestroyed())
	{
		if (UWorld* World = GetWorld())
		{
			if (World->WorldType == EWorldType::Editor || World->WorldType == EWorldType::Inactive)
			{
				auto ClearAcousticObjectsRemovedFromSceneImpl = [](TMap<UObject*, UStkAcousticData*>& ObjectsAcousticData)
				{
					TArray<UObject*> ObjectsToRemove;
					for (TPair<UObject*, UStkAcousticData*> StkObjectAcousticData : ObjectsAcousticData)
					{
						bool bShouldBeRemoved = !StkObjectAcousticData.Key ||
							(StkObjectAcousticData.Key->HasAnyFlags(RF_ArchetypeObject) && !StkObjectAcousticData.Key->GetOuter()->IsInBlueprint());

						UStkAcousticModel* AcousticModel = StkObjectAcousticData.Value->AcousticModel;
						if (bShouldBeRemoved)
						{
							ObjectsToRemove.Add(StkObjectAcousticData.Key);
							if (AcousticModel)
							{
								AcousticModel->Remove(StkObjectAcousticData.Key);
							}
						}
					}
					for (UObject* ObjectToRemove : ObjectsToRemove)
					{
						ObjectsAcousticData.Remove(ObjectToRemove);
					}
				};

				ClearAcousticObjectsRemovedFromSceneImpl(StkObjectsAcousticData);
				if (IsPersistentLevelActor())
				{
					if (UStkProjectData* ProjectData = UStkProjectData::Get())
					{
						ClearAcousticObjectsRemovedFromSceneImpl(ProjectData->StkArchetypesAcousticData);
					}
				}
			}
		}
	}
}
#endif

void AStkScene::OnMeshesAddedToModel(SoundToolKit::FStkModelInternalData& ModelData)
{
	if (!ModelData.bIsAddedToScene)
	{
		StkGameModule->AddModel(ModelData.Native);
		ModelData.bIsAddedToScene = true;
	}

	if (ModelData.bIsModified)
	{
		SetModelMeshes(ModelData.Native, ModelData.GetMeshes());
	}

	if (UWorld* World = GetWorld())
	{
		if (!World->bStartup && OnSceneGeometryChanged)
		{
			OnSceneGeometryChanged();
		}
	}
}

void AStkScene::OnMeshesRemovedFromModel(SoundToolKit::FStkModelInternalData& ModelData)
{
	if (ModelData.bIsModified)
	{
		SetModelMeshes(ModelData.Native, ModelData.GetMeshes());
	}

	if (ModelData.bIsAddedToScene && (ModelData.IsEmpty() || !ModelData.bIsModified))
	{
		StkGameModule->RemoveModel(ModelData.Native);
		ModelData.bIsAddedToScene = false;
	}

	if (OnSceneGeometryChanged)
	{
		OnSceneGeometryChanged();
	}
}

void AStkScene::OnUpdateVolumes()
{
	StkGameModule->GetAudioOutput().SetMasterVolume(MasterVolume);
	StkGameModule->GetAudio()->scene().setSpatialVolume(SpatialVolume);
	StkGameModule->GetAudio()->scene().setReverbVolume(ReverbVolume);
}

void AStkScene::OnUpdateVolumes(const FName& PropertyName)
{
	if (PropertyName.IsEqual(GET_MEMBER_NAME_CHECKED(AStkScene, MasterVolume)))
	{
		StkGameModule->GetAudioOutput().SetMasterVolume(MasterVolume);
	}
	else if (PropertyName.IsEqual(GET_MEMBER_NAME_CHECKED(AStkScene, SpatialVolume)))
	{
		StkGameModule->GetAudio()->scene().setSpatialVolume(SpatialVolume);
	}
	else if (PropertyName.IsEqual(GET_MEMBER_NAME_CHECKED(AStkScene, ReverbVolume)))
	{
		StkGameModule->GetAudio()->scene().setReverbVolume(ReverbVolume);
	}
}

void AStkScene::OnUpdateReflection()
{
	if (bEnableReflection)
	{
		StkGameModule->GetAudio()->scene().enableSpatialEffect(stk::SpatialEffectType::Reflection);
	}
	else
	{
		StkGameModule->GetAudio()->scene().disableSpatialEffect(stk::SpatialEffectType::Reflection);
	}
}

void AStkScene::OnUpdateDiffraction()
{
	if (bEnableDiffraction)
	{
		StkGameModule->GetAudio()->scene().enableSpatialEffect(stk::SpatialEffectType::Diffraction);
	}
	else
	{
		StkGameModule->GetAudio()->scene().disableSpatialEffect(stk::SpatialEffectType::Diffraction);
	}
}

void AStkScene::OnUpdateTransmission()
{
	if (bEnableTransmission)
	{
		StkGameModule->GetAudio()->scene().enableSpatialEffect(stk::SpatialEffectType::Transmission);
	}
	else
	{
		StkGameModule->GetAudio()->scene().disableSpatialEffect(stk::SpatialEffectType::Transmission);
	}
}

void AStkScene::OnUpdateOcclusionEffects()
{
	OnUpdateReflection();
	OnUpdateTransmission();
	OnUpdateDiffraction();
}

void AStkScene::OnUpdateOcclusionEffects(const FName& PropertyName)
{
	if (PropertyName.IsEqual(GET_MEMBER_NAME_CHECKED(AStkScene, bEnableReflection)))
	{
		OnUpdateReflection();
	}
	else if (PropertyName.IsEqual(GET_MEMBER_NAME_CHECKED(AStkScene, bEnableTransmission)))
	{
		OnUpdateTransmission();
	}
	else if (PropertyName.IsEqual(GET_MEMBER_NAME_CHECKED(AStkScene, bEnableDiffraction)))
	{
		OnUpdateDiffraction();
	}
}

void AStkScene::OnUpdateHRTF()
{
	if (bEnableHRTF)
	{
		StkGameModule->GetAudioOutput().EnableHrtf();
	}
	else
	{
		StkGameModule->GetAudioOutput().DisableHrtf();
	}
}

void AStkScene::OnUpdateAttenuation()
{
	if (bEnableAttenuation)
	{
		StkGameModule->GetAudio()->scene().enableSpatialEffect(stk::SpatialEffectType::Attenuation);
	}
	else
	{
		StkGameModule->GetAudio()->scene().disableSpatialEffect(stk::SpatialEffectType::Attenuation);
	}
}

void AStkScene::OnUpdateSpatialEffects()
{
	OnUpdateHRTF();
	OnUpdateAttenuation();
}

void AStkScene::OnUpdateSpatialEffects(const FName& PropertyName)
{
	if (PropertyName.IsEqual(GET_MEMBER_NAME_CHECKED(AStkScene, bEnableHRTF)))
	{
		OnUpdateHRTF();
	}
	else if (PropertyName.IsEqual(GET_MEMBER_NAME_CHECKED(AStkScene, bEnableAttenuation)))
	{
		OnUpdateAttenuation();
	}
}

void AStkScene::OnUpdateSpeedOfSound()
{
	StkGameModule->GetAudio()->scene().acousticMedium().setSpeedOfSound(SpeedOfSound);
}

void AStkScene::OnUpdateDamping()
{
	if (bEnableDamping)
	{
		StkGameModule->GetAudio()->scene().acousticMedium().dampingWithDistance().enable();
	}
	else
	{
		StkGameModule->GetAudio()->scene().acousticMedium().dampingWithDistance().disable();
	}
}

void AStkScene::OnUpdateDampingCoefficients()
{
	stk::IEffect::Coefficients Coefficients{
		Damping.Band125Hz,
		Damping.Band250Hz,
		Damping.Band500Hz,
		Damping.Band1000Hz,
		Damping.Band2000Hz,
		Damping.Band4000Hz,
		Damping.Band8000Hz,
		Damping.Band16000Hz };
	StkGameModule->GetAudio()->scene().acousticMedium().dampingWithDistance().setCoefficients(Coefficients);
}

void AStkScene::OnUpdateAcousticMedium()
{
	OnUpdateSpeedOfSound();
	OnUpdateDampingCoefficients();
	OnUpdateDamping();
}

void AStkScene::OnUpdateAcousticMedium(const FName& PropertyName, const FName& MemberPropertyName)
{
	if (PropertyName.IsEqual(GET_MEMBER_NAME_CHECKED(AStkScene, SpeedOfSound)))
	{
		OnUpdateSpeedOfSound();
	}
	else if (PropertyName.IsEqual(GET_MEMBER_NAME_CHECKED(AStkScene, bEnableDamping)))
	{
		OnUpdateDamping();
	}
	else if (MemberPropertyName.IsEqual(GET_MEMBER_NAME_CHECKED(AStkScene, Damping)))
	{
		OnUpdateDampingCoefficients();
	}
}
