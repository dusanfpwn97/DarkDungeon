//$ Copyright 2015-20, Code Respawn Technologies Pvt Ltd - All Rights Reserved $//

#pragma once
#include "CoreMinimal.h"
#include "Frameworks/GridFlow/Common/Widgets/SGridFlowItemOverlayDelegates.h"

#include "EdGraph/EdGraph.h"
#include "GridFlowAbstractEdGraph.generated.h"

class UGridFlowAbstractEdGraphNode;

UCLASS()
class DUNGEONARCHITECTEDITOR_API UGridFlowAbstractEdGraph : public UEdGraph {
    GENERATED_UCLASS_BODY()

public:
    TWeakObjectPtr<class UGridFlowAbstractGraph> ScriptGraph;

    FGridFlowItemWidgetEvent OnItemWidgetClicked;
    FGuid SelectedItemId;
};
