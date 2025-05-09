//$ Copyright 2015-20, Code Respawn Technologies Pvt Ltd - All Rights Reserved $//

#include "Frameworks/GridFlow/ExecGraph/Tasks/Tilemap/GridFlowTaskTilemap_Optimize.h"

#include "Frameworks/GridFlow/ExecGraph/GridFlowExecTaskAttribute.h"
#include "Frameworks/GridFlow/ExecGraph/GridFlowExecTaskAttributeMacros.h"
#include "Frameworks/GridFlow/Tilemap/GridFlowTilemap.h"

#include "Containers/Queue.h"

void UGridFlowTaskTilemap_Optimize::Execute(const FGridFlowExecutionInput& Input, FGridFlowExecutionOutput& Output) {
    if (Input.IncomingNodeOutputs.Num() == 0) {
        Output.ErrorMessage = "Missing Input";
        Output.ExecutionResult = EGridFlowTaskExecutionResult::FailHalt;
        return;
    }
    if (Input.IncomingNodeOutputs.Num() > 1) {
        Output.ErrorMessage = "Only one input allowed";
        Output.ExecutionResult = EGridFlowTaskExecutionResult::FailHalt;
        return;
    }

    Output.State = Input.IncomingNodeOutputs[0].State->Clone();

    if (!Output.State->AbstractGraph) {
        Output.ErrorMessage = "Invalid Input Layout Graph";
        Output.ExecutionResult = EGridFlowTaskExecutionResult::FailHalt;
        return;
    }

    if (!Output.State->Tilemap) {
        Output.ErrorMessage = "Invalid Input Tilemap";
        Output.ExecutionResult = EGridFlowTaskExecutionResult::FailHalt;
        return;
    }

    UGridFlowAbstractGraph* Graph = Output.State->AbstractGraph;
    UGridFlowTilemap* Tilemap = Output.State->Tilemap;

    DiscardDistantTiles(Tilemap);

    Output.ExecutionResult = EGridFlowTaskExecutionResult::Success;
}

void UGridFlowTaskTilemap_Optimize::DiscardDistantTiles(UGridFlowTilemap* Tilemap) {
    int32 Width = Tilemap->GetWidth();
    int32 Height = Tilemap->GetHeight();
    TQueue<FGridFlowTilemapCell*> Queue;


    static const int ChildOffsets[] = {
        -1, 0,
        1, 0,
        0, -1,
        0, 1
    };

    // Fill initial points on the queue
    TMap<FIntPoint, int32> DistanceFromLayout;
    {
        for (FGridFlowTilemapCell& Cell : Tilemap->GetCells()) {
            if (Cell.bLayoutCell) {
                Queue.Enqueue(&Cell);
                DistanceFromLayout.Add(Cell.TileCoord, 0);
            }
        }
    }

    // Flood fill and find tile distances from layout edge
    {
        FGridFlowTilemapCell* Cell = nullptr;
        while (Queue.Dequeue(Cell)) {
            // Traverse the children
            int32 ChildDistance = DistanceFromLayout[Cell->TileCoord] + 1;

            for (int i = 0; i < 4; i++) {
                int nx = Cell->TileCoord.X + ChildOffsets[i * 2 + 0];
                int ny = Cell->TileCoord.Y + ChildOffsets[i * 2 + 1];
                if (nx >= 0 && nx < Width && ny >= 0 && ny < Height) {
                    FGridFlowTilemapCell& NCell = Tilemap->Get(nx, ny);
                    if (NCell.bLayoutCell) continue;
                    bool bTraverseChild = (!DistanceFromLayout.Contains(NCell.TileCoord) || ChildDistance <
                        DistanceFromLayout[NCell.TileCoord]);

                    if (bTraverseChild) {
                        int32& NDistance = DistanceFromLayout.FindOrAdd(NCell.TileCoord);
                        NDistance = ChildDistance;
                        Queue.Enqueue(&NCell);
                    }
                }
            }
        }
    }

    // Clear out the tiles that are far away
    {
        DiscardDistanceFromLayout = FMath::Max(0, DiscardDistanceFromLayout);
        for (FGridFlowTilemapCell& Cell : Tilemap->GetCells()) {
            if (!DistanceFromLayout.Contains(Cell.TileCoord)) continue;
            if (Cell.bLayoutCell) continue;
            if (DistanceFromLayout[Cell.TileCoord] > DiscardDistanceFromLayout) {
                Cell = FGridFlowTilemapCell();
            }
        }
    }
}


bool UGridFlowTaskTilemap_Optimize::GetParameter(const FString& InParameterName, FGridFlowAttribute& OutValue) {
    GRIDFLOWATTR_GET_INT(DiscardDistanceFromLayout);

    return false;
}

bool UGridFlowTaskTilemap_Optimize::SetParameter(const FString& InParameterName, const FGridFlowAttribute& InValue) {
    GRIDFLOWATTR_SET_INT(DiscardDistanceFromLayout);

    return false;
}

bool UGridFlowTaskTilemap_Optimize::SetParameterSerialized(const FString& InParameterName,
                                                           const FString& InSerializedText) {
    GRIDFLOWATTR_SET_PARSE_INT(DiscardDistanceFromLayout);

    return false;
}
