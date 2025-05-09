//$ Copyright 2015-20, Code Respawn Technologies Pvt Ltd - All Rights Reserved $//

#pragma once
#include "CoreMinimal.h"
#include "Builders/SnapMap/Connection/SnapMapConnectionConstants.h"
#include "Core/DungeonConfig.h"

#include "Engine/DataAsset.h"
#include "SnapMapDungeonConfig.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(SnapMapDungeonConfigLog, Log, All);

USTRUCT()
struct DUNGEONARCHITECTRUNTIME_API FSnapMapModuleDatabaseConnectionInfo {
    GENERATED_USTRUCT_BODY()

    UPROPERTY(VisibleAnywhere, Category = Module)
    FGuid ConnectionId;

    UPROPERTY(VisibleAnywhere, Category = Module)
    FTransform Transform;

    UPROPERTY(VisibleAnywhere, Category = Module)
    class USnapMapConnectionInfo* ConnectionInfo;

    UPROPERTY(VisibleAnywhere, Category = Module)
    ESnapMapConnectionConstraint ConnectionConstraint;
};

USTRUCT()
struct DUNGEONARCHITECTRUNTIME_API FSnapMapModuleDatabaseItem {
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, Category = Module)
    TSoftObjectPtr<UWorld> Level;

    UPROPERTY(EditAnywhere, Category = Module)
    FName Category = "Room";

    UPROPERTY(VisibleAnywhere, Category = Module)
    FBox ModuleBounds;

    UPROPERTY(VisibleAnywhere, Category = Module)
    TArray<FSnapMapModuleDatabaseConnectionInfo> Connections;
};

uint32 GetTypeHash(const FSnapMapModuleDatabaseItem& A);


UCLASS()
class DUNGEONARCHITECTRUNTIME_API USnapMapModuleDatabase : public UDataAsset {
    GENERATED_BODY()
public:

    UPROPERTY(EditAnywhere, Category = Module)
    TArray<FSnapMapModuleDatabaseItem> Modules;

};

UCLASS(Blueprintable)
class DUNGEONARCHITECTRUNTIME_API USnapMapDungeonConfig : public UDungeonConfig {
    GENERATED_UCLASS_BODY()

public:
    /** A module database asset that contains the references of the modules to use for building the dungeon */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dungeon)
    USnapMapModuleDatabase* ModuleDatabase;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dungeon)
    class UDungeonFlow* DungeonFlowGraph;

    /** 
       Can the rooms / modules be rotated while stitching them together. Disable this for isometric / platformer games 
       where the rooms are designed to be viewed at a certain angle 
    */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dungeon)
    bool bAllowModuleRotations = true;

    /**
     When modules are stitched together, the builder makes sure they do not overlap.  This parameter is used to 
     control the tolerance level.  If set to 0, even the slightest overlap with a nearby module would not create an adjacent module
     Leaving to a small number like 100, would tolerate an overlap with nearby module by 100 unreal units.
     Adjust this depending on your art asset
    */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dungeon)
    int32 CollisionTestContraction;

    /** The max processing time (in seconds) before bailing out. This keeps the build function from hanging if it doesn't find a solution */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dungeon)
    float MaxProcessingTimeSecs = 4.0f;

    /** If the dungeon build fails, it will be retried with another seed multiple times (see field NumBuildRetries) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dungeon)
    bool bSupportBuildRetries = false;

    /** If the dungeon build fails, it will be retried with another seed multiple tiles based on this count */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dungeon, Meta = (EditCondition = "bSupportBuildRetries"))
    int32 NumBuildRetries = 20;
};
