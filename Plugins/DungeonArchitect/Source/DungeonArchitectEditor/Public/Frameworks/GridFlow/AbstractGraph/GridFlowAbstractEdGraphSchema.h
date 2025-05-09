//$ Copyright 2015-20, Code Respawn Technologies Pvt Ltd - All Rights Reserved $//

#pragma once
#include "CoreMinimal.h"
#include "Core/Utils/DungeonGraphUtils.h"

#include "EdGraph/EdGraphSchema.h"
#include "GridFlowAbstractEdGraphSchema.generated.h"

class UGridFlowAbstractEdGraph;


UCLASS()
class DUNGEONARCHITECTEDITOR_API UGridFlowAbstractEdGraphSchema : public UEdGraphSchema {
    GENERATED_UCLASS_BODY()
public:

    // Begin EdGraphSchema interface
    void GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const override;
    void GetContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;
    const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const override;
    class FConnectionDrawingPolicy* CreateConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID,
                                                                  float InZoomFactor, const FSlateRect& InClippingRect,
                                                                  class FSlateWindowElementList& InDrawElements,
                                                                  class UEdGraph* InGraphObj) const override;
    FLinearColor GetPinTypeColor(const FEdGraphPinType& PinType) const override;
    bool ShouldHidePinDefaultValue(UEdGraphPin* Pin) const override;

#if WITH_EDITOR
    bool TryCreateConnection(UEdGraphPin* A, UEdGraphPin* B) const override;
    void BreakNodeLinks(UEdGraphNode& TargetNode) const override;
    void BreakPinLinks(UEdGraphPin& TargetPin, bool bSendsNodeNotifcation) const override;
    void BreakSinglePinLink(UEdGraphPin* SourcePin, UEdGraphPin* TargetPin) const override;
#endif // WITH_EDITOR
    // End EdGraphSchema interface

};


/** Action to add a node to the graph */
USTRUCT()
struct DUNGEONARCHITECTEDITOR_API FGridFlowAbstractSchemaAction_NewNode : public FDungeonSchemaAction_NewNode {
    GENERATED_USTRUCT_BODY();

    FGridFlowAbstractSchemaAction_NewNode()
        : FDungeonSchemaAction_NewNode() {
    }

    FGridFlowAbstractSchemaAction_NewNode(const FText& InNodeCategory, const FText& InMenuDesc, const FText& InToolTip,
                                          const int32 InGrouping)
        : FDungeonSchemaAction_NewNode(InNodeCategory, InMenuDesc, InToolTip, InGrouping) {
    }

    UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, FVector2D Location,
                                bool bSelectNewNode = true) override;
};
