//$ Copyright 2015-20, Code Respawn Technologies Pvt Ltd - All Rights Reserved $//

#pragma once
#include "CoreMinimal.h"
#include "Builders/Grid/GridDungeonToolData.h"
#include "Core/LevelEditor/EditorMode/DungeonEdModeHandler.h"
#include "GridDungeonEdModeHandler.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(GridDungeonEdModeHandlerLog, Log, All);

UCLASS()
class UGridDungeonEdModeHandler : public UDungeonEdModeHandler {
    GENERATED_BODY()

public:
    TSharedPtr<FDungeonEdModeRenderer> CreateRenderer() override;
    void ApplyPaintData(const FString& TransactionName, const TArray<FIntVector>& StrokeData,
                        EGridPaintToolCellType CellType, bool bRemove);
    virtual void SetActiveTool(TSharedPtr<IDungeonEdTool> NewTool) override;
    TSharedPtr<SWidget> CreateToolkitWidget() override;

protected:
    void OnUpdate(const FSceneView* View, FViewport* Viewport) override;
};
