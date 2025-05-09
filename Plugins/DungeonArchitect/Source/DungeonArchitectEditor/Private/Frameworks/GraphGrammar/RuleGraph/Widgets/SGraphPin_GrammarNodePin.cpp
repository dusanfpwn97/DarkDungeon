//$ Copyright 2015-20, Code Respawn Technologies Pvt Ltd - All Rights Reserved $//

#include "Frameworks/GraphGrammar/RuleGraph/Widgets/SGraphPin_GrammarNodePin.h"


void SGraphPin_GrammarNodePin::Construct(const FArguments& InArgs, UEdGraphPin* InPin) {
    this->SetCursor(EMouseCursor::Default);

    typedef SGraphPin_GrammarNodePin ThisClass;

    bShowLabel = true;
    IsEditable = true;

    GraphPinObj = InPin;
    check(GraphPinObj != NULL);

    const UEdGraphSchema* Schema = GraphPinObj->GetSchema();
    check(Schema);

    // Set up a hover for pins that is tinted the color of the pin.
    SBorder::Construct(SBorder::FArguments()
                       .BorderImage(this, &SGraphPin_GrammarNodePin::GetPinBorder)
                       .BorderBackgroundColor(this, &ThisClass::GetPinColor)
                       .OnMouseButtonDown(this, &ThisClass::OnPinMouseDown)
                       .Cursor(this, &ThisClass::GetPinCursor)
                       .Padding(FMargin(5.0f))
    );
}

TSharedRef<SWidget> SGraphPin_GrammarNodePin::GetDefaultValueWidget() {
    return SNew(STextBlock);
}

const FSlateBrush* SGraphPin_GrammarNodePin::GetPinBorder() const {
    return FEditorStyle::GetBrush(TEXT("Graph.StateNode.Body"));
}

FSlateColor SGraphPin_GrammarNodePin::GetPinColor() const {
    static const FLinearColor MeshPinColor(1.0f, 0.7f, 0.0f);
    static const FLinearColor MarkerPinColor(0.3f, 0.3f, 1.0f);
    static const FLinearColor DarkColor(0.02f, 0.02f, 0.02f);
    if (!IsHovered()) {
        return DarkColor;
    }
    return MeshPinColor;
}
