//$ Copyright 2015-20, Code Respawn Technologies Pvt Ltd - All Rights Reserved $//

#pragma once
#include "CoreMinimal.h"
#include "SViewportToolBar.h"

/**
* A level viewport toolbar widget that is placed in a viewport
*/
class DUNGEONARCHITECTEDITOR_API SSnapMapConnectionPreview3DViewportToolbar : public SViewportToolBar {
public:
SLATE_BEGIN_ARGS(SSnapMapConnectionPreview3DViewportToolbar) {
        }

        SLATE_ARGUMENT(TSharedPtr<class SSnapMapConnectionPreview3DViewport>, Viewport)
    SLATE_END_ARGS()

    void Construct(const FArguments& InArgs);

    TSharedRef<SWidget> GeneratePropertiesMenu() const;
    TSharedRef<SWidget> GenerateCameraMenu() const;
    TSharedPtr<FExtender> GetViewMenuExtender();

private:
    /** The viewport that we are in */
    TWeakPtr<class SSnapMapConnectionPreview3DViewport> Viewport;

};


/**
* Class containing commands for level viewport actions
*/
class DUNGEONARCHITECTEDITOR_API
    FSnapMapConnectionEditorViewportCommands : public TCommands<FSnapMapConnectionEditorViewportCommands> {
public:

    FSnapMapConnectionEditorViewportCommands()
        : TCommands<FSnapMapConnectionEditorViewportCommands>
        (
            TEXT("LAThemeEditorViewport"), // Context name for fast lookup
            NSLOCTEXT("Contexts", "SnapMapConnectionViewport", "SnapMap Door Viewport"),
            // Localized context name for displaying
            NAME_None, //TEXT("EditorViewport"), // Parent context name.  
            FEditorStyle::GetStyleSetName() // Icon Style Set
        ) {
    }

    TSharedPtr<FUICommandInfo> ToggleDebugData;

public:
    /** Registers our commands with the binding system */
    void RegisterCommands() override;

};
