//$ Copyright 2015-20, Code Respawn Technologies Pvt Ltd - All Rights Reserved $//

#pragma once
#include "CoreMinimal.h"
#include "AdvancedPreviewScene.h"

/**
 * Encapsulates a simple scene setup for preview or thumbnail rendering.
 */
class DUNGEONARCHITECTEDITOR_API FDungeonFlowPreviewScene : public FAdvancedPreviewScene {
public:
    FDungeonFlowPreviewScene(ConstructionValues CVS = ConstructionValues());
};
