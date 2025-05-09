//$ Copyright 2015-19, Code Respawn Technologies Pvt Ltd - All Rights Reserved $//

namespace UnrealBuildTool.Rules
{
    public class DungeonArchitectEditor : ModuleRules
    {
        public DungeonArchitectEditor(ReadOnlyTargetRules Target) : base(Target)
        {
            PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
            PublicIncludePaths.AddRange(
                new string[]
                {
                    // ... add public include paths required here ...
                }
            );

            PrivateIncludePaths.AddRange(
                new[]
                {
                    "DungeonArchitectEditor/Private"
                    // ... add other private include paths required here ...
                }
            );

            PrivateIncludePathModuleNames.AddRange(
                new[]
                {
                    "Settings",
                    "IntroTutorials",
                    "AssetTools",
                    "MessageLog"
                }
            );

            PublicDependencyModuleNames.AddRange(
                new[]
                {
                    "Core",
                    "CoreUObject",
                    "Engine",
                    "EditorStyle",
                    "UnrealEd",
                    "KismetWidgets",
                    "GraphEditor",
                    "Foliage",
                    "AdvancedPreviewScene",
                    "Kismet",
                    "PlacementMode",
                    "EditorWidgets",
                    "ApplicationCore",
                    "AssetRegistry",
                    "RHI",
                    "AddContentDialog"
                }
            );

            PrivateDependencyModuleNames.AddRange(
                new[]
                {
                    "InputCore",
                    "Slate",
                    "SlateCore",
                    "RenderCore",
                    "PropertyEditor",
                    "WorkspaceMenuStructure",
                    "LevelEditor",
                    "EditorStyle",
                    "ContentBrowser",
                    "DungeonArchitectRuntime",
                    "Projects",
                    "ToolMenus",
                    "Json",
                    "JsonUtilities"
                    // ... add private dependencies that you statically link with here ...
                }
            );

            DynamicallyLoadedModuleNames.AddRange(
                new string[]
                {
                    // ... add any modules that your module loads dynamically here ...
                }
            );
        }
    }
}