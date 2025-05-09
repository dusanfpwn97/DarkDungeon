//$ Copyright 2015-20, Code Respawn Technologies Pvt Ltd - All Rights Reserved $//

#pragma once
#include "CoreMinimal.h"
#include "Core/Rules/DungeonTransformLogic.h"
#include "IsaacDungeonTransformLogic.generated.h"

struct FCell;
class UIsaacDungeonModel;

/**
*
*/
UCLASS(Blueprintable, HideDropDown)
class DUNGEONARCHITECTRUNTIME_API UIsaacDungeonTransformLogic : public UDungeonTransformLogic {
    GENERATED_BODY()

public:

    UFUNCTION(BlueprintNativeEvent, Category = "Dungeon")
    void GetNodeOffset(UIsaacDungeonModel* Model, FTransform& Offset);
    virtual void GetNodeOffset_Implementation(UIsaacDungeonModel* Model, FTransform& Offset);

};
