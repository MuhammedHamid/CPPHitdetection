// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Codelikeme_CPP : ModuleRules
{
	public Codelikeme_CPP(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
