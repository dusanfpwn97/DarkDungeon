//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#include "StkExtensions.h"
#include "StkCommon.h"
#include "StkSettings.h"
#include "StkGeometryComponent.h"
#include "StkGameModule.h"

#include "Modules/ModuleManager.h"
#include "Math/Color.h"
#include "Misc/FileHelper.h"
#include "Components/LineBatchComponent.h"
#include "ProceduralMeshComponent.h"
#include "Materials/Material.h"
#include "Materials/MaterialExpressionVectorParameter.h"
#include "EngineUtils.h"

namespace
{
	TMap<stk::PathVertexType, FColor> GetPathColors()
	{
		static TMap<stk::PathVertexType, FColor> PathColors;
		if (PathColors.Num() == 0)
		{
			PathColors.Add(stk::PathVertexType::Source, FColor::Black);
			PathColors.Add(stk::PathVertexType::Receiver, FColor::Red);
			PathColors.Add(stk::PathVertexType::Reflection, FColor::Green);
			PathColors.Add(stk::PathVertexType::Scattering, FColor::Cyan);
			PathColors.Add(stk::PathVertexType::Transmission, FColor::Yellow);
			PathColors.Add(stk::PathVertexType::Diffraction, FColor::Blue);
		}

		return PathColors;
	}
}

AStkExtensions::AStkExtensions()
	: bShowLiveSoundPaths(false)
	, bShowAcousticScene(false)
	, NumberOfModels(0)
	, NumberOfMeshSections(0)
	, NumberOfTriangles(0)
	, StkSoundPathsCache(stk_ex::diagnostics::ISoundPathsCache::create(SoundToolKit::Utils::GetGameModule().GetAudio()))
	, AcousticSceneMeshComponent(CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("AcousticSceneMesh")))
	, AcousticSceneMaterial(CreateDefaultSubobject<UMaterial>(TEXT("AcousticSceneMaterial")))
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.SetTickFunctionEnable(true);
	PrimaryActorTick.bStartWithTickEnabled = true;

	SoundPathsDrawer = NewObject<ULineBatchComponent>();
	SoundPathsDrawer->bCalculateAccurateBounds = false;

	AcousticSceneMeshComponent->SetMobility(EComponentMobility::Static);
	AcousticSceneMeshComponent->SetHiddenInGame(!bShowAcousticScene);

	UMaterialExpressionVectorParameter* Color = CreateDefaultSubobject<UMaterialExpressionVectorParameter>(TEXT("AcousticSceneMaterialColor"));
	Color->ParameterName = "Color";
	Color->DefaultValue = FLinearColor(/*Coral*/1.00, 0.50, 0.31);
	AcousticSceneMaterial->EmissiveColor.Expression = Color;
	AcousticSceneMaterial->TwoSided = true;
	AcousticSceneMaterial->PostLoad();

	bLockLocation = true;

	SetRootComponent(AcousticSceneMeshComponent);
}

#if WITH_EDITOR
bool AStkExtensions::CanEditChange(const FProperty* InProperty) const
{
	bool bBaseEditable = Super::CanEditChange(InProperty);

	return bBaseEditable && (GetWorld() ? GetWorld()->WorldType == EWorldType::PIE : false);
}
#endif

void AStkExtensions::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	SoundToolKit::FStkGameModule& StkGameModule = SoundToolKit::Utils::GetGameModule();
	StkGameModule.ConnectOnSceneInitialized([this](AStkScene* Scene)
	{
		Scene->ConnectOnSceneGeometryChanged([this] { bShouldRefreshAcousticScene = true; });
	});
}

void AStkExtensions::BeginPlay()
{
	SoundPathsDrawer->RegisterComponentWithWorld(GetWorld());

	Super::BeginPlay();
}

void AStkExtensions::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (SoundPathsDrawer->IsRegistered())
	{
		SoundPathsDrawer->UnregisterComponent();
	}

	Super::EndPlay(EndPlayReason);
}

void AStkExtensions::Tick(float DeltaSeconds)
{
	if (bShouldRefreshAcousticScene)
	{
		if (NumberOfQueuedSoundToolKitCommands.Increment() == 1)
		{
			bShouldRefreshAcousticScene = false;
			RegenerateAcousticSceneMesh();
		}
		else
		{
			NumberOfQueuedSoundToolKitCommands.Decrement();
		}
	}

	if (bShowLiveSoundPaths)
	{
		HideSoundPaths();
		ShowSoundPaths();
	}

	Super::Tick(DeltaSeconds);
}

void AStkExtensions::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	const FName& PropertyName = PropertyChangedEvent.GetPropertyName();
	if (PropertyName.IsEqual(GET_MEMBER_NAME_CHECKED(AStkExtensions, bShowLiveSoundPaths)))
	{
		if (bShowLiveSoundPaths)
		{
			StkSoundPathsCache->enableCaching();
		}
		else
		{
			StkSoundPathsCache->disableCaching();
			HideSoundPaths();
		}
	}

	AcousticSceneMeshComponent->SetHiddenInGame(!bShowAcousticScene);

	Super::PostEditChangeProperty(PropertyChangedEvent);
}

void AStkExtensions::PostActorCreated()
{
	Super::PostActorCreated();

	AcousticSceneMeshComponent->SetWorldLocation(FVector(0, 0, 0));
}

bool AStkExtensions::IsSoundPathsCachingEnabled() const
{
	return StkSoundPathsCache->isCachingEnabled();
}

void AStkExtensions::ShowSoundPaths()
{
	using namespace SoundToolKit;

	static const TMap<stk::PathVertexType, FColor> PathColors{ GetPathColors() };

	StkSoundPathsCache->getCachedPaths([&copiedPaths = StkLiveSoundPaths](stk::ArrayView<stk_ex::diagnostics::ISoundPathsCache::SoundPathView> paths)
	{
		copiedPaths.resize(paths.size());
		for (size_t i = 0; i < paths.size(); ++i)
		{
			copiedPaths[i].assign(paths[i].begin(), paths[i].end());
		}
	});

	for (size_t j = 0; j < StkLiveSoundPaths.size(); ++j)
	{
		for (size_t i = 1; i < StkLiveSoundPaths[j].size(); ++i)
		{
			DrawLine(
				Utils::ConvertVector(StkLiveSoundPaths[j][i - 1].position),
				Utils::ConvertVector(StkLiveSoundPaths[j][i].position),
				PathColors[StkLiveSoundPaths[j][i].type]);
		}
	}
}

void AStkExtensions::HideSoundPaths()
{
	FlushLines();
}

void AStkExtensions::DrawLine(const FVector& Start, const FVector& End, const FColor& Color)
{
	SoundPathsDrawer->DrawLine(Start, End, Color, SDPG_World, Thickness);
}

void AStkExtensions::FlushLines()
{
	SoundPathsDrawer->Flush();
}

void AStkExtensions::RegenerateAcousticSceneMesh()
{
#if WITH_EDITOR
	AcousticSceneMeshComponent->ClearAllMeshSections();

	SoundToolKit::FStkGameModule& StkGameModule = SoundToolKit::Utils::GetGameModule();

	NumberOfModels = 0;
	NumberOfMeshSections = 0;
	NumberOfTriangles = 0;

	// Incrementation for command GetModels was already done in Tick() function.
	StkGameModule.GetModels([this](stk::ArrayView<stk::SharedResource<stk::IModel>> StkModels)
	{
		for (stk::SharedResource<stk::IModel> StkModel : StkModels)
		{
			if (StkModel)
			{
				++NumberOfModels;

				NumberOfQueuedSoundToolKitCommands.Increment();
				StkModel->getMeshes([this](stk::ArrayView<stk::SharedResource<stk::IMesh>> Meshes)
				{
					for (stk::SharedResource<stk::IMesh> Mesh : Meshes)
					{
						NumberOfQueuedSoundToolKitCommands.Increment();
						Mesh->getFaces([this, MeshNumber{ NumberOfMeshSections++ }](stk::ArrayView<stk::face> Faces)
						{
							TArray<FVector> Vertices;
							TArray<int32> Triangles;
							int32 VerticesCounter = 0;
							for (stk::face Face : Faces)
							{
								++NumberOfTriangles;

								Vertices.Add(SoundToolKit::Utils::ConvertVector(Face.a));
								Vertices.Add(SoundToolKit::Utils::ConvertVector(Face.b));
								Vertices.Add(SoundToolKit::Utils::ConvertVector(Face.c));

								Triangles.Add(VerticesCounter++);
								Triangles.Add(VerticesCounter++);
								Triangles.Add(VerticesCounter++);
							}

							AcousticSceneMeshComponent->CreateMeshSection(MeshNumber,
								Vertices, Triangles, TArray<FVector>(), TArray<FVector2D>(), TArray<FColor>(), TArray<FProcMeshTangent>(), false);
							AcousticSceneMeshComponent->SetMaterial(MeshNumber, AcousticSceneMaterial);

							NumberOfQueuedSoundToolKitCommands.Decrement();
						});
					}

					NumberOfQueuedSoundToolKitCommands.Decrement();
				});
			}
		}

		NumberOfQueuedSoundToolKitCommands.Decrement();
	});
#endif
}
