//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
using System;
using System.IO;
using UnrealBuildTool;

namespace UnrealBuildTool.Rules
{
    public class StkGameModule : ModuleRules
    {
        private new string PluginDirectory
        {
            get { return Path.Combine(ModuleDirectory, "..", ".."); }
        }

        private string ResourcesDirectory
        {
            get { return Path.Combine(PluginDirectory, "Resources"); }
        }

        private string ThirdPartyLibsDirectory
        {
            get { return Path.Combine(PluginDirectory, "Source", "ThirdParty", "Libs"); }
        }

        void AddResourceDependencies()
        {
            RuntimeDependencies.Add(Path.Combine(ResourcesDirectory, "assets", "*"));
            RuntimeDependencies.Add(Path.Combine(ResourcesDirectory, "bqc_hrtf.bin"));
            RuntimeDependencies.Add(Path.Combine(ResourcesDirectory, "diffraction_table_100_20.bin"));
        }

        public StkGameModule(ReadOnlyTargetRules Target) : base(Target)
        {
            PrivatePCHHeaderFile = "Private/StkCommon.h";
            PCHUsage = PCHUsageMode.NoSharedPCHs;
            CppStandard = CppStandardVersion.Cpp17;
            bEnforceIWYU = true;
            bEnableExceptions = true;

            PrivateIncludePaths.AddRange(
                new string[]
                {
                    "ThirdParty/Headers",
                });

            PublicDependencyModuleNames.AddRange(
                new string[]
                {
                    "Core",
                    "Engine",
                    "CoreUObject",
                });

            PrivateDependencyModuleNames.AddRange(
                new string[]
                {
                    "Core",
                    "Engine",
                    "CoreUObject",
                    "Projects",
                    "Landscape",
                    "AudioExtensions",
                });

            if (Target.bBuildEditor)
            {
                PrivateDependencyModuleNames.Add("UnrealEd");
            }

            PublicAdditionalLibraries.AddRange(
                new string[]
                {
                    Path.Combine(ThirdPartyLibsDirectory, "libstk_64_v141_Release_AVX.lib"),
                    Path.Combine(ThirdPartyLibsDirectory, "libstk_ex_64_v141_Release_AVX.lib"),
                });

            AddResourceDependencies();
        }
    }
}
