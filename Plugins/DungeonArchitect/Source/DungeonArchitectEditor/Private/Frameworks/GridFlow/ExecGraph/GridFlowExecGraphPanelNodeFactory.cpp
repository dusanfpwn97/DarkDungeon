//$ Copyright 2015-20, Code Respawn Technologies Pvt Ltd - All Rights Reserved $//

#include "Frameworks/GridFlow/ExecGraph/GridFlowExecGraphPanelNodeFactory.h"

#include "Frameworks/GridFlow/ExecGraph/Nodes/GridFlowExecEdGraphNodeBase.h"
#include "Frameworks/GridFlow/ExecGraph/Nodes/GridFlowExecEdGraphNodes.h"
#include "Frameworks/GridFlow/ExecGraph/Widgets/SGraphNode_GridFlowExecNode.h"

TSharedPtr<class SGraphNode> FGridFlowExecGraphPanelNodeFactory::CreateNode(UEdGraphNode* Node) const {
    if (UGridFlowExecEdGraphNodeBase* ExecNode = Cast<UGridFlowExecEdGraphNodeBase>(Node)) {
        TSharedPtr<SGraphNode_GridFlowExecNode> SNode = SNew(SGraphNode_GridFlowExecNode, ExecNode);

        if (ExecNode->IsA<UGridFlowExecEdGraphNode_Result>()) {
            SNode->SetBorderColor(FLinearColor(0.08f, 0.16f, 0.08f));
        }
        return SNode;
    }
    return nullptr;
}
