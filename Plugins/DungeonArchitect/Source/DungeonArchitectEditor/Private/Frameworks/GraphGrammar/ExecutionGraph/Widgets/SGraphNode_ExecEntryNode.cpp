//$ Copyright 2015-20, Code Respawn Technologies Pvt Ltd - All Rights Reserved $//

#include "Frameworks/GraphGrammar/ExecutionGraph/Widgets/SGraphNode_ExecEntryNode.h"

#include "Frameworks/GraphGrammar/ExecutionGraph/Nodes/EdGraphNode_ExecEntryNode.h"

#include "SGraphPin.h"
#include "Widgets/SBoxPanel.h"

/////////////////////////////////////////////////////
// SGraphNodeAnimStateEntry

void SGraphNode_ExecEntryNode::Construct(const FArguments& InArgs, UEdGraphNode_ExecEntryNode* InNode) {
    this->GraphNode = InNode;

    this->SetCursor(EMouseCursor::CardinalCross);

    this->UpdateGraphNode();
}

void SGraphNode_ExecEntryNode::GetNodeInfoPopups(FNodeInfoContext* Context,
                                                 TArray<FGraphInformationPopupInfo>& Popups) const {

}

FSlateColor SGraphNode_ExecEntryNode::GetBorderBackgroundColor() const {
    FLinearColor InactiveStateColor(0.08f, 0.08f, 0.08f);
    FLinearColor ActiveStateColorDim(0.4f, 0.3f, 0.15f);
    FLinearColor ActiveStateColorBright(1.f, 0.6f, 0.35f);

    return InactiveStateColor;
}

void SGraphNode_ExecEntryNode::UpdateGraphNode() {
    InputPins.Empty();
    OutputPins.Empty();

    // Reset variables that are going to be exposed, in case we are refreshing an already setup node.
    RightNodeBox.Reset();
    LeftNodeBox.Reset();


    FLinearColor TitleShadowColor(0.6f, 0.6f, 0.6f);

    this->ContentScale.Bind(this, &SGraphNode::GetContentScale);
    this->GetOrAddSlot(ENodeZone::Center)
        .HAlign(HAlign_Center)
        .VAlign(VAlign_Center)
    [
        SNew(SBorder)
			.BorderImage(FEditorStyle::GetBrush("Graph.StateNode.Body"))
			.Padding(0)
			.BorderBackgroundColor(this, &SGraphNode_ExecEntryNode::GetBorderBackgroundColor)
        [
            SNew(SOverlay)

            // PIN AREA
            + SOverlay::Slot()
              .HAlign(HAlign_Fill)
              .VAlign(VAlign_Fill)
              .Padding(10.0f)
            [
                SAssignNew(RightNodeBox, SVerticalBox)
            ]
        ]
    ];

    CreatePinWidgets();
}

void SGraphNode_ExecEntryNode::AddPin(const TSharedRef<SGraphPin>& PinToAdd) {
    PinToAdd->SetOwner(SharedThis(this));
    RightNodeBox->AddSlot()
                .HAlign(HAlign_Fill)
                .VAlign(VAlign_Fill)
                .FillHeight(1.0f)
    [
        PinToAdd
    ];
    OutputPins.Add(PinToAdd);
}

FText SGraphNode_ExecEntryNode::GetPreviewCornerText() const {
    return NSLOCTEXT("SGraphNodeAnimStateEntry", "CornerTextDescription", "Entry point for Execution Graph");
}
