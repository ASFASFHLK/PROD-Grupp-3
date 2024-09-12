// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BooBreakfast : ModuleRules
{
	public BooBreakfast(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
