//$ Copyright 2015-20, Code Respawn Technologies Pvt Ltd - All Rights Reserved $//

#include "Frameworks/GraphGrammar/ExecutionGraph/ExecutionGraphConnectionDrawingPolicy.h"

#include "Core/LevelEditor/Customizations/DungeonArchitectStyle.h"
#include "Frameworks/GraphGrammar/ExecutionGraph/EdGraph_FlowExec.h"
#include "Frameworks/GraphGrammar/ExecutionGraph/Nodes/EdGraphNode_ExecRuleNode.h"

#include "EdGraph/EdGraphNode.h"
#include "Framework/Commands/GenericCommands.h"
#include "Rendering/DrawElements.h"
#include "SGraphNode.h"
#include "ToolMenu.h"
#include "ToolMenuSection.h"

#define LOCTEXT_NAMESPACE "GrammarGraphConnectionDrawingPolicy"

FExecutionGraphConnectionDrawingPolicy::FExecutionGraphConnectionDrawingPolicy(
    int32 InBackLayerID, int32 InFrontLayerID, float ZoomFactor, const FSlateRect& InClippingRect,
    FSlateWindowElementList& InDrawElements, UEdGraph* InGraphObj)
    : FConnectionDrawingPolicy(InBackLayerID, InFrontLayerID, ZoomFactor, InClippingRect, InDrawElements)
      , GraphObj(InGraphObj) {
    DependentArrowImage = FDungeonArchitectStyle::Get().GetBrush(TEXT("DA.FlowEd.Graph.ArrowDependent"));
    DependentArrowRadius = DependentArrowImage->ImageSize * ZoomFactor * 0.5f;
}

void FExecutionGraphConnectionDrawingPolicy::DetermineWiringStyle(UEdGraphPin* OutputPin, UEdGraphPin* InputPin,
                                                                  /*inout*/ FConnectionParams& Params) {
    const FLinearColor DefaultColor(1.0f, 1.0f, 1.0f);
    Params.WireThickness = 1.5f;
    Params.WireColor = DefaultColor;
    Params.bUserFlag1 = false; // bidirectional

    if (OutputPin && InputPin) {
        UEdGraphNode_ExecNodeBase* SourceNode = Cast<UEdGraphNode_ExecNodeBase>(OutputPin->GetOwningNode());
        UEdGraphNode_ExecNodeBase* DestNode = Cast<UEdGraphNode_ExecNodeBase>(InputPin->GetOwningNode());

    }
    const bool bDeemphasizeUnhoveredPins = HoveredPins.Num() > 0;
    if (bDeemphasizeUnhoveredPins) {
        ApplyHoverDeemphasis(OutputPin, InputPin, /*inout*/ Params.WireThickness, /*inout*/ Params.WireColor);
    }
}

void FExecutionGraphConnectionDrawingPolicy::Draw(TMap<TSharedRef<SWidget>, FArrangedWidget>& InPinGeometries,
                                                  FArrangedChildren& ArrangedNodes) {
    // Build an acceleration structure to quickly find geometry for the nodes
    NodeWidgetMap.Empty();
    for (int32 NodeIndex = 0; NodeIndex < ArrangedNodes.Num(); ++NodeIndex) {
        FArrangedWidget& CurWidget = ArrangedNodes[NodeIndex];
        TSharedRef<SGraphNode> ChildNode = StaticCastSharedRef<SGraphNode>(CurWidget.Widget);
        UEdGraphNode* NodeObj = ChildNode->GetNodeObj();
        NodeWidgetMap.Add(NodeObj, NodeIndex);
    }
    // Now draw
    FConnectionDrawingPolicy::Draw(InPinGeometries, ArrangedNodes);
}

void FExecutionGraphConnectionDrawingPolicy::DetermineLinkGeometry(FArrangedChildren& ArrangedNodes,
                                                                   TSharedRef<SWidget>& OutputPinWidget,
                                                                   UEdGraphPin* OutputPin, UEdGraphPin* InputPin,
                                                                   /*out*/ FArrangedWidget*& StartWidgetGeometry,
                                                                   /*out*/ FArrangedWidget*& EndWidgetGeometry) {
    UEdGraphNode* OutputNode = OutputPin->GetOwningNode();
    UEdGraphNode* InputNode = InputPin->GetOwningNode();

    if (NodeWidgetMap.Contains(OutputNode)) {
        StartWidgetGeometry = &ArrangedNodes[NodeWidgetMap[OutputNode]];
    }
    if (NodeWidgetMap.Contains(InputNode)) {
        EndWidgetGeometry = &ArrangedNodes[NodeWidgetMap[InputNode]];
    }
}

void FExecutionGraphConnectionDrawingPolicy::DrawPreviewConnector(const FGeometry& PinGeometry,
                                                                  const FVector2D& StartPoint,
                                                                  const FVector2D& EndPoint, UEdGraphPin* Pin) {
    bool bBiDirectional = false;
    FConnectionParams Params;
    Params.WireThickness = 1.0f;
    Params.WireColor = FLinearColor::White;
    Params.bDrawBubbles = false;
    Params.bUserFlag1 = bBiDirectional;
    DetermineWiringStyle(Pin, nullptr, /*inout*/ Params);

    if (Pin->Direction == EGPD_Output) {
        DrawSplineWithArrow(FGeometryHelper::FindClosestPointOnGeom(PinGeometry, EndPoint), EndPoint, Params);
    }
    else {
        DrawSplineWithArrow(FGeometryHelper::FindClosestPointOnGeom(PinGeometry, StartPoint), StartPoint, Params);
    }
}


void FExecutionGraphConnectionDrawingPolicy::DrawSplineWithArrow(const FVector2D& StartAnchorPoint,
                                                                 const FVector2D& EndAnchorPoint,
                                                                 const FConnectionParams& Params) {
    // hacky: use bBidirectional flag to reverse direction of connection (used by debugger)
    bool Bidirectional = Params.bUserFlag1;
    const FVector2D& P0 = Bidirectional ? EndAnchorPoint : StartAnchorPoint;
    const FVector2D& P1 = Bidirectional ? StartAnchorPoint : EndAnchorPoint;

    Internal_DrawLineWithArrow(P0, P1, Params);
}

void FExecutionGraphConnectionDrawingPolicy::Internal_DrawLineWithArrow(const FVector2D& StartAnchorPoint,
                                                                        const FVector2D& EndAnchorPoint,
                                                                        const FConnectionParams& Params) {
    //@TODO: Should this be scaled by zoom factor?
    bool bDependencyLink = Params.bUserFlag2;
    const FVector2D ArrowHeadRadius = bDependencyLink ? DependentArrowRadius : ArrowRadius;
    const FSlateBrush* ArrowHeadImage = bDependencyLink ? DependentArrowImage : ArrowImage;

    const FVector2D DeltaPos = EndAnchorPoint - StartAnchorPoint;
    const FVector2D UnitDelta = DeltaPos.GetSafeNormal();
    const FVector2D Normal = FVector2D(DeltaPos.Y, -DeltaPos.X).GetSafeNormal();

    // Come up with the final start/end points
    const FVector2D LengthBias = ArrowHeadRadius.X * UnitDelta;
    const FVector2D StartPoint = StartAnchorPoint;
    FVector2D EndPoint = EndAnchorPoint - LengthBias;

    // Draw a line
    if (bDependencyLink) {
        DrawConnection(WireLayerID, StartPoint, EndPoint - LengthBias, Params);
    }
    else {
        DrawConnection(WireLayerID, StartPoint, EndPoint, Params);
    }


    const FVector2D ArrowDrawPos = EndPoint - ArrowHeadRadius;
    const float AngleInRadians = FMath::Atan2(DeltaPos.Y, DeltaPos.X);

    // Draw the arrow
    FSlateDrawElement::MakeRotatedBox(
        DrawElementsList,
        ArrowLayerID,
        FPaintGeometry(ArrowDrawPos, ArrowHeadImage->ImageSize * ZoomFactor, ZoomFactor),
        ArrowHeadImage,
        //ClippingRect,
        ESlateDrawEffect::None,
        AngleInRadians,
        TOptional<FVector2D>(),
        FSlateDrawElement::RelativeToElement,
        Params.WireColor
    );

}

void FExecutionGraphConnectionDrawingPolicy::DrawSplineWithArrow(const FGeometry& StartGeom, const FGeometry& EndGeom,
                                                                 const FConnectionParams& Params) {
    // Get a reasonable seed point (halfway between the boxes)
    const FVector2D StartCenter = FGeometryHelper::CenterOf(StartGeom);
    const FVector2D EndCenter = FGeometryHelper::CenterOf(EndGeom);
    const FVector2D SeedPoint = (StartCenter + EndCenter) * 0.5f;

    // Find the (approximate) closest points between the two boxes
    const FVector2D StartAnchorPoint = FGeometryHelper::FindClosestPointOnGeom(StartGeom, SeedPoint);
    const FVector2D EndAnchorPoint = FGeometryHelper::FindClosestPointOnGeom(EndGeom, SeedPoint);

    DrawSplineWithArrow(StartAnchorPoint, EndAnchorPoint, Params);
}

void FExecutionGraphConnectionDrawingPolicy::DrawConnection(int32 LayerId, const FVector2D& Start, const FVector2D& End,
                                                            const FConnectionParams& Params) {
    const FVector2D& P0 = Start;
    const FVector2D& P1 = End;

    const FVector2D Delta = End - Start;
    const FVector2D NormDelta = Delta.GetSafeNormal();

    const FVector2D P0Tangent = NormDelta;
    const FVector2D P1Tangent = NormDelta;

    // Draw the spline itself
    FSlateDrawElement::MakeDrawSpaceSpline(
        DrawElementsList,
        LayerId,
        P0, P0Tangent,
        P1, P1Tangent,
        //ClippingRect,
        Params.WireThickness,
        ESlateDrawEffect::None,
        Params.WireColor
    );

    if (Params.bDrawBubbles) {
        // This table maps distance along curve to alpha
        FInterpCurve<float> SplineReparamTable;
        float SplineLength = MakeSplineReparamTable(P0, P0Tangent, P1, P1Tangent, SplineReparamTable);

        // Draw bubbles on the spline
        const float BubbleSpacing = 64.f * ZoomFactor;
        const float BubbleSpeed = 192.f * ZoomFactor;
        const FVector2D BubbleSize = BubbleImage->ImageSize * ZoomFactor * 0.1f * Params.WireThickness;

        float Time = (FPlatformTime::Seconds() - GStartTime);
        const float BubbleOffset = FMath::Fmod(Time * BubbleSpeed, BubbleSpacing);
        const int32 NumBubbles = FMath::CeilToInt(SplineLength / BubbleSpacing);
        for (int32 i = 0; i < NumBubbles; ++i) {
            const float Distance = (static_cast<float>(i) * BubbleSpacing) + BubbleOffset;
            if (Distance < SplineLength) {
                const float Alpha = SplineReparamTable.Eval(Distance, 0.f);
                FVector2D BubblePos = FMath::CubicInterp(P0, P0Tangent, P1, P1Tangent, Alpha);
                BubblePos -= (BubbleSize * 0.5f);

                FSlateDrawElement::MakeBox(
                    DrawElementsList,
                    LayerId,
                    FPaintGeometry(BubblePos, BubbleSize, ZoomFactor),
                    BubbleImage,
                    //ClippingRect,
                    ESlateDrawEffect::None,
                    Params.WireColor
                );
            }
        }
    }
}


FConnectionDrawingPolicy* FEditorFlowExecGraphSupport::CreateDrawingPolicy(
    int32 InBackLayerID, int32 InFrontLayerID, float InZoomFactor, const FSlateRect& InClippingRect,
    class FSlateWindowElementList& InDrawElements, class UEdGraph* InGraphObj) const {
    return new FExecutionGraphConnectionDrawingPolicy(InBackLayerID, InFrontLayerID, InZoomFactor, InClippingRect,
                                                      InDrawElements, InGraphObj);
}

void FEditorFlowExecGraphSupport::GetContextMenuActions(class UToolMenu* Menu,
                                                        class UGraphNodeContextMenuContext* Context) const {
    const UEdGraph* CurrentGraph = Context->Graph;
    TArray<UEdGraphNode_ExecNodeBase*> SelectedNodes;
    for (UEdGraphNode* Node : CurrentGraph->Nodes) {
        if (Node->IsSelected() && Node->IsA<UEdGraphNode_ExecNodeBase>()) {
            SelectedNodes.Add(Cast<UEdGraphNode_ExecNodeBase>(Node));
        }
    }

    if (SelectedNodes.Num() == 2) {
        UEdGraphNode_ExecNodeBase* A = SelectedNodes[0];
        UEdGraphNode_ExecNodeBase* B = SelectedNodes[1];
        bool bNodesConnected = A->GetOutputPin()->LinkedTo.Contains(B->GetInputPin())
            || B->GetOutputPin()->LinkedTo.Contains(A->GetInputPin());

        if (bNodesConnected) {
            FToolMenuSection& Section = Menu->AddSection("ExecutionGraphMenu",
                                                         LOCTEXT("ExecutionGraphMenuHeader", "Execution Graph"));
            Section.AddMenuEntry(FGenericCommands::Get().Delete);
        }
    }
}

#undef LOCTEXT_NAMESPACE
