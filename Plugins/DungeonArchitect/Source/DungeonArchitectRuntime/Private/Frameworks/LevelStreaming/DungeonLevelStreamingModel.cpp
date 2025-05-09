//$ Copyright 2015-20, Code Respawn Technologies Pvt Ltd - All Rights Reserved $//

#include "Frameworks/LevelStreaming/DungeonLevelStreamingModel.h"

#include "Core/Dungeon.h"
#include "Core/Utils/EditorService/IDungeonEditorService.h"
#include "Frameworks/LevelStreaming/DungeonLevelStreamingNavigation.h"

#include "Engine/Engine.h"
#include "Engine/LevelStreaming.h"
#include "Engine/LevelStreamingDynamic.h"
#include "Engine/World.h"

DEFINE_LOG_CATEGORY(LogLevelStreamingModel);

///////////////////////////////// UDungeonStreamingChunk ///////////////////////////////// 
UDungeonStreamingChunk::UDungeonStreamingChunk(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    LevelStreaming = nullptr;
}

void UDungeonStreamingChunk::RegisterStreamingCallbacks() {
    if (LevelStreaming) {
        LevelStreaming->OnLevelLoaded.AddDynamic(this, &UDungeonStreamingChunk::HandleChunkLoaded);
        LevelStreaming->OnLevelUnloaded.AddDynamic(this, &UDungeonStreamingChunk::HandleChunkUnloaded);
        LevelStreaming->OnLevelShown.AddDynamic(this, &UDungeonStreamingChunk::HandleChunkVisible);
        LevelStreaming->OnLevelHidden.AddDynamic(this, &UDungeonStreamingChunk::HandleChunkHidden);
    }
}


ULevelStreamingDynamic* FLevelStreamLoader::LoadLevelInstanceBySoftObjectPtr(
    UObject* WorldContextObject, TSoftObjectPtr<UWorld> Level, uint32 InstanceId, FVector Location, FRotator Rotation,
    bool& bOutSuccess, UPackage*& OutLevelPackage) {
    bOutSuccess = false;
    OutLevelPackage = nullptr;

    UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
    if (!World) {
        return nullptr;
    }

    // Check whether requested map exists, this could be very slow if LevelName is a short package name
    if (Level.IsNull()) {
        return nullptr;
    }

    bOutSuccess = true;
    return LoadLevelInstance_Internal(World, Level.GetLongPackageName(), InstanceId, Location, Rotation,
                                      OutLevelPackage);
}

ULevelStreamingDynamic* FLevelStreamLoader::LoadLevelInstance_Internal(UWorld* World, const FString& LongPackageName,
                                                                       uint32 InstanceId, FVector Location,
                                                                       FRotator Rotation, UPackage*& OutLevelPackage) {
    if (!World) return nullptr;

    // Create Unique Name for sub-level package
    const FString ShortPackageName = FPackageName::GetShortName(LongPackageName);
    const FString PackagePath = FPackageName::GetLongPackagePath(LongPackageName);
    //FString UniqueLevelPackageName = PackagePath + TEXT("/") + World->StreamingLevelsPrefix + ShortPackageName;
    //UniqueLevelPackageName += TEXT("_LI_") + FString::FromInt(InstanceId);

    uint32 Hash = HashCombine(GetTypeHash(Location), GetTypeHash(Rotation.Euler()));
    FString UniqueLevelPackageName = FString::Printf(
        TEXT("%s/%s%s_LI_%s_%d_%u"), *PackagePath, *World->StreamingLevelsPrefix, *ShortPackageName, *World->GetName(),
        InstanceId, Hash);

    if (!World->IsGameWorld()) {
        UPackage* LevelPackage = CreatePackage(nullptr, *UniqueLevelPackageName);
        LevelPackage->SetFlags(RF_Transient | RF_DuplicateTransient);
        OutLevelPackage = LevelPackage;
    }
    else {
        UniqueLevelPackageName += TEXT("G");
    }

    ULevelStreamingDynamic* StreamingLevel = NewObject<ULevelStreamingDynamic>(
        World, ULevelStreamingDynamic::StaticClass(), NAME_None, RF_Transient | RF_DuplicateTransient, nullptr);
    StreamingLevel->SetWorldAssetByPackageName(FName(*UniqueLevelPackageName));

    StreamingLevel->LevelColor = FColor::MakeRandomColor();
    StreamingLevel->SetShouldBeLoaded(false);
    StreamingLevel->SetShouldBeVisible(false);
    StreamingLevel->bShouldBlockOnLoad = false;
    StreamingLevel->bInitiallyLoaded = false;
    StreamingLevel->bInitiallyVisible = false;
    // Transform
    StreamingLevel->LevelTransform = FTransform(Rotation, Location);
    // Map to Load
    StreamingLevel->PackageNameToLoad = FName(*LongPackageName);

    // Add the new level to world.
    World->AddStreamingLevel(StreamingLevel);

    return StreamingLevel;
}

void UDungeonStreamingChunk::CreateLevelStreaming(UObject* WorldContextObject, TSoftObjectPtr<UWorld> Level,
                                                  uint32 InstanceId, FVector Location, FRotator Rotation,
                                                  bool& bOutSuccess) {
    LevelStreaming = FLevelStreamLoader::LoadLevelInstanceBySoftObjectPtr(
        WorldContextObject, Level, InstanceId, Location, Rotation, bOutSuccess, LevelPackage);
    RegisterStreamingCallbacks();
}

void UDungeonStreamingChunk::SetStreamingLevelState(bool bInVisible, bool bInLoaded) {
    if (!LevelStreaming) {
        bShouldBeLoaded = false;
        bShouldBeVisible = false;
        return;
    }

    bool bRequiresUpdate = RequiresStateUpdate(bInVisible, bInLoaded);

    if (bRequiresUpdate) {
        bShouldBeLoaded = bInLoaded;
        bShouldBeVisible = bInVisible;

        LevelStreaming->bShouldBlockOnUnload = false;
        LevelStreaming->bShouldBlockOnLoad = false;
        LevelStreaming->SetShouldBeLoaded(bInLoaded);
        LevelStreaming->SetShouldBeVisible(bInVisible);
    }
}

bool UDungeonStreamingChunk::RequiresStateUpdate(bool bInVisible, bool bInLoaded) const {
    if (!LevelStreaming) return false;
    return (bInVisible != bShouldBeVisible) || (bInLoaded != bShouldBeLoaded);
}

void UDungeonStreamingChunk::DestroyChunk(UWorld* InWorld) {
    if (LevelStreaming) {
        LevelStreaming->SetIsRequestingUnloadAndRemoval(true);
        LevelStreaming->SetShouldBeVisible(false);
        LevelStreaming->SetShouldBeLoaded(false);
    }
}

UPackage* UDungeonStreamingChunk::GetLevelPackage() const {
    return LevelPackage;
}

ULevel* UDungeonStreamingChunk::GetLoadedLevel() const {
    return LevelStreaming ? LevelStreaming->GetLoadedLevel() : nullptr;
}

ULevelStreaming* UDungeonStreamingChunk::GetStreamingLevel() const {
    return LevelStreaming;
}

FTransform UDungeonStreamingChunk::GetLevelTransform() const {
    return LevelStreaming ? LevelStreaming->LevelTransform : FTransform::Identity;
}

void UDungeonStreamingChunk::HandleChunkVisible() {
    UDungeonLevelStreamingModel* StreamingModel = Cast<UDungeonLevelStreamingModel>(GetOuter());
    if (StreamingModel && StreamingModel->StreamingNavigation) {
        StreamingModel->StreamingNavigation->AddLevelNavigation(LevelStreaming->GetLoadedLevel(), Bounds);
    }
    bIsVisible = true;
}

void UDungeonStreamingChunk::HandleChunkHidden() {
    UDungeonLevelStreamingModel* StreamingModel = Cast<UDungeonLevelStreamingModel>(GetOuter());
    if (LevelStreaming && StreamingModel && StreamingModel->StreamingNavigation) {
        StreamingModel->StreamingNavigation->RemoveLevelNavigation(LevelStreaming->GetLoadedLevel());
    }
    bIsVisible = false;
}

void UDungeonStreamingChunk::HandleChunkLoaded() {
    bIsLoaded = true;
}

void UDungeonStreamingChunk::HandleChunkUnloaded() {
    bIsLoaded = false;
}

///////////////////////////////// UDungeonLevelStreamingModel /////////////////////////////////

UDungeonLevelStreamingModel::UDungeonLevelStreamingModel(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer) {
    StreamingNavigation = ObjectInitializer.CreateDefaultSubobject<UDungeonLevelStreamingNavigation>(
        this, "StreamingNavigation");
    StreamingNavigation->bAutoResizeNavVolume = true;
}

void UDungeonLevelStreamingModel::Initialize(UWorld* InWorld) {
    StreamingNavigation->Initialize(InWorld);
}

void UDungeonLevelStreamingModel::Release(UWorld* InWorld) {
    StreamingNavigation->Release();

    TArray<ULevelStreaming*> LevelsToRemove;
    TArray<UPackage*> LevelPackages;

    for (UDungeonStreamingChunk* Chunk : Chunks) {
        if (Chunk) {
            // Save the level package so we can unload it later on
            UPackage* LevelPackage = Chunk->GetLevelPackage();
            if (LevelPackage) {
                LevelPackage->SetDirtyFlag(false);
                LevelPackages.Add(LevelPackage);
            }

            ULevelStreaming* LevelToRemove = Chunk->GetStreamingLevel();
            if (LevelToRemove) {
                LevelsToRemove.Add(LevelToRemove);
            }

            // Destroy the chunk
            Chunk->DestroyChunk(InWorld);
        }
    }
    Chunks.Empty();

    if (LevelsToRemove.Num() > 0) {
        // Make sure the streaming levels in the world are flushed before we unload the levels
        InWorld->FlushLevelStreaming(EFlushLevelStreamingType::Full);
        InWorld->RemoveStreamingLevels(LevelsToRemove);
    }

    if (LevelPackages.Num() > 0) {
        TSharedPtr<IDungeonEditorService> EditorService = IDungeonEditorService::Get();
        if (EditorService.IsValid()) {
            if (!EditorService->UnloadPackages(LevelPackages)) {
                UE_LOG(LogLevelStreamingModel, Error, TEXT("Failed to unload streaming chunk level packages"));
            }
        }
    }
}

void UDungeonLevelStreamingModel::NotifyInitialChunksLoaded() {
    ADungeon* Dungeon = Cast<ADungeon>(GetOuter());
    OnInitialChunksLoaded.Broadcast(Dungeon);
    bNotifiedInitialChunkLoadEvent = true;
}
