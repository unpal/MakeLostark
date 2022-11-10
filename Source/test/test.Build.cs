// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class test : ModuleRules
{
	public test(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { 
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore", 
			"HeadMountedDisplay",
			"NavigationSystem",
			"AIModule",
			"GamePlayTasks",
			"Niagara",
			"UMG"
		});
		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.Add(ModuleDirectory);
	}
}
