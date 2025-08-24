// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class COD : ModuleRules
{
	public COD(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(new string[] { "COD" });

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "AIModule", "UMG", "MediaAssets" +
			"" });
	}
}
