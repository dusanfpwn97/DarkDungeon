//$ Copyright 2015-20, Code Respawn Technologies Pvt Ltd - All Rights Reserved $//

#pragma once
#include "CoreMinimal.h"
#include "Builders/Isaac/IsaacDungeonModel.h"
#include "Core/DungeonBuilder.h"
#include "Core/DungeonModel.h"
#include "Core/Utils/PMRandom.h"
#include "DungeonThemeAsset.h"

#include "Containers/Queue.h"
#include "IsaacDungeonBuilder.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(IsaacDungeonBuilderLog, Log, All);

class ADungeon;
class UIsaacDungeonConfig;
class UIsaacDungeonModel;
class FIsaacRoomLayoutBuilder;
class FIsaacRoomFactory;

struct FLevelGrowthNode;
/**
*
*/
UCLASS(Experimental)
class DUNGEONARCHITECTRUNTIME_API UIsaacDungeonBuilder : public UDungeonBuilder {
    GENERATED_BODY()

public:
    void BuildDungeonImpl(UWorld* World) override;
    void EmitDungeonMarkers_Implementation() override;
    void DrawDebugData(UWorld* InWorld, bool bPersistant = false, float lifeTime = -1.0f) override;
    bool SupportsBackgroundTask() const override { return false; }
    void MirrorDungeon() override;
    TSubclassOf<UDungeonModel> GetModelClass() override;
    TSubclassOf<UDungeonConfig> GetConfigClass() override;
    TSubclassOf<UDungeonToolData> GetToolDataClass() override;
    TSubclassOf<UDungeonQuery> GetQueryClass() override;
    bool ProcessSpatialConstraint(UDungeonSpatialConstraint* SpatialConstraint, const FTransform& Transform,
                                  FQuat& OutRotationOffset) override;
    void GetDefaultMarkerNames(TArray<FString>& OutMarkerNames) override;

private:
    void GenerateLevelLayout();
    void AddNextRoomNode(TSharedPtr<FIsaacRoomFactory> roomFactory, TQueue<FLevelGrowthNode>& queue,
                         TSet<FIntVector>& visited, int maxRooms, FIsaacRoomPtr parentRoom, int direction,
                         float probability);
    void ConnectRoomsWithDoors(FIsaacRoomPtr roomA, FIsaacRoomPtr roomB);
    FIsaacRoomPtr GetRoomAt(const FIntVector& position);
    bool ContainsDoorBetween(int roomA, int roomB);
    void CreateDoor(FIsaacRoomPtr roomA, FIsaacRoomPtr roomB, float ratio);
    FIsaacRoomLayout GenerateEmptyRoomLayout();
    void CreateMarkerAt(float gridX, float gridY, float angle, const FString& markerName,
                        const FVector& roomBasePosition, const FVector& tileSize);
    void EmitBoundaryMarkers(const FString& markerName, EIsaacRoomTileType adjacentTile1,
                             EIsaacRoomTileType adjacentTile2,
                             const FIsaacRoom& room, int32 roomWidth, int32 roomHeight, const FVector& roomBasePosition,
                             const FVector& tileSize);

protected:

    void MirrorDungeonWithVolume(ADungeonMirrorVolume* MirrorVolume) override;
    bool PerformSelectionLogic(const TArray<UDungeonSelectorLogic*>& SelectionLogics,
                               const FPropSocket& socket) override;
    FTransform PerformTransformLogic(const TArray<UDungeonTransformLogic*>& TransformLogics,
                                     const FPropSocket& socket) override;

private:
    void BuildLayout();

private:
    int32 _CellIdCounter;
    UIsaacDungeonModel* isaacModel;
    UIsaacDungeonConfig* isaacConfig;

    TArray<FIsaacRoomPtr> rooms;
    TArray<FIsaacDoorPtr> doors;
};
