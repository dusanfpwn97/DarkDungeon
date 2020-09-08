//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
using System.IO;
using UnrealBuildTool;

namespace UnrealBuildTool.Rules
{
    public class StkEditorModule : ModuleRules
    {
        public StkEditorModule(ReadOnlyTargetRules Target) : base(Target)
        {
            PrivatePCHHeaderFile = "../StkGameModule/Private/StkCommon.h";
            PCHUsage = PCHUsageMode.NoSharedPCHs;
            CppStandard = CppStandardVersion.Cpp17;
            bEnforceIWYU = true;

            PrivateIncludePaths.AddRange(
                new string[]
                {
                    "StkGameModule/Private",
                    "ThirdParty/Headers",
                });

            PublicDependencyModuleNames.AddRange(
                new string[]
                {
                    "Core",
                    "InputCore",
                });

            PrivateDependencyModuleNames.AddRange(
                new string[]
                {
                    "Core",
                    "Engine",
                    "CoreUObject",
                    "UnrealEd",
                    "Projects",
                    "Settings",
                    "PlacementMode",
                    "Slate",
                    "SlateCore",
                    "PropertyEditor",
                    "EditorStyle",
                    "DesktopPlatform",
                    "Landscape",
                    "ProceduralMeshComponent",
                    "StkGameModule",
                });
        }
    }
}
