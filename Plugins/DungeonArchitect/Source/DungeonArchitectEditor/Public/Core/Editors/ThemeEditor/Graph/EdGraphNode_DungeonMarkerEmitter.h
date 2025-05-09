//$ Copyright 2015-20, Code Respawn Technologies Pvt Ltd - All Rights Reserved $//

#pragma once
#include "CoreMinimal.h"
#include "Core/Editors/ThemeEditor/Graph/EdGraphNode_DungeonBase.h"
#include "EdGraphNode_DungeonMarkerEmitter.generated.h"

UCLASS()
class DUNGEONARCHITECTEDITOR_API UEdGraphNode_DungeonMarkerEmitter : public UEdGraphNode_DungeonBase {
    GENERATED_UCLASS_BODY()

    // Begin UEdGraphNode interface.
    void AllocateDefaultPins() override;
    FLinearColor GetNodeTitleColor() const override;
    FText GetTooltipText() const override;
    FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
    // End UEdGraphNode interface.

public:
    virtual UEdGraphPin* GetInputPin() const override { return Pins[0]; }
    virtual UEdGraphPin* GetOutputPin() const override { return nullptr; }
    void AutowireNewNode(UEdGraphPin* FromPin) override;

public:
    UPROPERTY()
    class UEdGraphNode_DungeonMarker* ParentMarker;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dungeon)
    FTransform Offset;
};
