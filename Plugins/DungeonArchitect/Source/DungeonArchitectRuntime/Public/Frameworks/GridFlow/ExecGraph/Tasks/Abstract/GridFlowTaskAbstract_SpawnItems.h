//$ Copyright 2015-20, Code Respawn Technologies Pvt Ltd - All Rights Reserved $//

#pragma once
#include "CoreMinimal.h"
#include "Frameworks/GridFlow/AbstractGraph/GridFlowAbstractItem.h"
#include "Frameworks/GridFlow/ExecGraph/GridFlowExecTask.h"
#include "GridFlowTaskAbstract_SpawnItems.generated.h"

UENUM()
enum class EridFlowTask_SpawnItemsMethod : uint8 {
    RandomRange UMETA(DisplayName = "Random Range"),
    LinearDifficulty UMETA(DisplayName = "Linear Difficulty")
};

UCLASS(Meta = (AbstractTask, Title = "Spawn Items", Tooltip = "Spawn items in the layout nodes", MenuPriority = 1300))
class DUNGEONARCHITECTRUNTIME_API UGridFlowTaskAbstract_SpawnItems : public UGridFlowExecTask {
    GENERATED_BODY()
public:
    /**
        The list of paths to spawn the items on

        Variable Name: Paths
    */
    UPROPERTY(EditAnywhere, Category = "Spawn Items")
    TArray<FString> Paths;

    /**
        The type of item to spawn

        Variable Name: [N/A]
    */
    UPROPERTY(EditAnywhere, Category = "Spawn Items")
    EGridFlowItemType ItemType = EGridFlowItemType::Enemy;

    /**
        The marker name for this item. Create a marker in the theme file with this name and add you assets there

        Variable Name: MarkerName
    */
    UPROPERTY(EditAnywhere, Category = "Spawn Items")
    FString MarkerName;

    /**
        If ItemType is set to custom, customize the visuals of the items in the graph preview

        Variable Name: [N/A]
    */
    UPROPERTY(EditAnywhere, Category = "Spawn Items")
    FGridFlowItemCustomInfo CustomItemInfo;

    /**
        Minimum number of items to spawn

        Variable Name: MinCount
    */
    UPROPERTY(EditAnywhere, Category = "Spawn Items")
    int32 MinCount = 1;

    /**
        Maximum number of items to spawn

        Variable Name: MaxCount
    */
    UPROPERTY(EditAnywhere, Category = "Spawn Items")
    int32 MaxCount = 4;

    /**
        The method to use to control the spawn

        Variable Name: [N/A]
    */
    UPROPERTY(EditAnywhere, Category = "Spawn Items")
    EridFlowTask_SpawnItemsMethod SpawnMethod = EridFlowTask_SpawnItemsMethod::LinearDifficulty;

    /**
        Control the random variance

        Variable Name: SpawnDistributionVariance
    */
    UPROPERTY(EditAnywhere, Category = "Spawn Items")
    float SpawnDistributionVariance = 0.2f;

    /**
        Each node in the path has a difficulty, with the first node having a difficulty of 0
        and the last node 1 and everything in between
        Start spawning only on nodes having difficulty greater than this value

        Variable Name: MinSpawnDifficulty
    */
    UPROPERTY(EditAnywhere, Category = "Spawn Items")
    float MinSpawnDifficulty = 0.0f;

    /**
        The probability of spawning in this node.  It might spawn as usual or not spawn anything at all depending
        on this value. 0 = 0% chance of spawning.  1 = 100% chance of spawning

        Variable Name: SpawnProbability
    */
    UPROPERTY(EditAnywhere, Category = "Spawn Items")
    float SpawnProbability = 1.0f;

    /**
        Debug: Show the difficulty of the nodes in this path

        Variable Name: [N/A]
    */
    UPROPERTY(EditAnywhere, Category = "Debug")
    bool bDebugShowDifficulty = false;

    /**
        Debug: The color of the debug data item

        Variable Name: [N/A]
    */
    UPROPERTY(EditAnywhere, Category = "Debug")
    FLinearColor DifficultyInfoColor = FLinearColor(0, 0, 0.5f);

public:
    void Execute(const FGridFlowExecutionInput& Input, FGridFlowExecutionOutput& Output) override;
    bool GetParameter(const FString& InParameterName, FGridFlowAttribute& OutValue) override;
    bool SetParameter(const FString& InParameterName, const FGridFlowAttribute& InValue) override;
    bool SetParameterSerialized(const FString& InParameterName, const FString& InSerializedText) override;

private:
    int32 GetSpawnCount(float Weight, const FRandomStream& Random);
};
