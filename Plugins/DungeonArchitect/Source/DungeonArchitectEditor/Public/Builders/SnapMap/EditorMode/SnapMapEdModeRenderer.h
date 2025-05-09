//$ Copyright 2015-20, Code Respawn Technologies Pvt Ltd - All Rights Reserved $//

#pragma once
#include "CoreMinimal.h"
#include "Core/LevelEditor/EditorMode/DungeonEdModeRenderer.h"

class USnapMapModel;
class USnapMapEdModeHandler;

class DUNGEONARCHITECTEDITOR_API FSnapMapEdModeRenderer : public FDungeonEdModeRenderer {
public:
    FSnapMapEdModeRenderer(USnapMapEdModeHandler* pModeHandler);
    void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI,
                TSharedPtr<IDungeonEdTool> ActiveTool) override;
    void Destroy() override;

private:
    USnapMapEdModeHandler* ModeHandler;
};
