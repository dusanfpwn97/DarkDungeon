//$ Copyright 2015-20, Code Respawn Technologies Pvt Ltd - All Rights Reserved $//

#pragma once
#include "CoreMinimal.h"
#include "DungeonThemeAsset.h"

#include "IDetailsView.h"

class FDungeonArchitectThemeGraphHandler : public FGCObject,
                                           public TSharedFromThis<FDungeonArchitectThemeGraphHandler> {
public:
    void Bind();
    void Initialize(TSharedPtr<SGraphEditor> InGraphEditor, TSharedPtr<IDetailsView> InPropertyEditor,
                    UDungeonThemeAsset* InPropBeingEdited);
    TSharedPtr<FUICommandList> GetCommands() const { return GraphEditorCommands; }

    /** Select every node in the graph */
    void SelectAllNodes();
    /** Whether we can select every node */
    bool CanSelectAllNodes() const;

    /** Deletes all the selected nodes */
    void DeleteSelectedNodes();

    bool CanDeleteNode(class UEdGraphNode* Node);

    /** Delete an array of Material Graph Nodes and their corresponding expressions/comments */
    void DeleteNodes(const TArray<class UEdGraphNode*>& NodesToDelete);

    /** Delete only the currently selected nodes that can be duplicated */
    void DeleteSelectedDuplicatableNodes();

    /** Whether we are able to delete the currently selected nodes */
    bool CanDeleteNodes() const;

    /** Copy the currently selected nodes */
    void CopySelectedNodes();
    /** Whether we are able to copy the currently selected nodes */
    bool CanCopyNodes() const;

    /** Paste the contents of the clipboard */
    void PasteNodes();
    bool CanPasteNodes() const;
    void PasteNodesHere(const FVector2D& Location);

    /** Cut the currently selected nodes */
    void CutSelectedNodes();
    /** Whether we are able to cut the currently selected nodes */
    bool CanCutNodes() const;

    /** Duplicate the currently selected nodes */
    void DuplicateNodes();
    /** Whether we are able to duplicate the currently selected nodes */
    bool CanDuplicateNodes() const;

    /** Called when the selection changes in the GraphEditor */
    void OnSelectedNodesChanged(const TSet<class UObject*>& NewSelection);

    /** Called when a node is double clicked */
    void OnNodeDoubleClicked(class UEdGraphNode* Node);


    void AddReferencedObjects(FReferenceCollector& Collector) override;

public:
    SGraphEditor::FGraphEditorEvents GraphEvents;

private:
    TSharedPtr<SGraphEditor> GraphEditor;
    TSharedPtr<IDetailsView> PropertyEditor;
    UDungeonThemeAsset* PropBeingEdited;
    TSharedPtr<FUICommandList> GraphEditorCommands;
};
