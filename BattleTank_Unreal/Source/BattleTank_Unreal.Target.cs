// Copyright Yurgen Hohmeyer 2017

using UnrealBuildTool;
using System.Collections.Generic;

public class BattleTank_UnrealTarget : TargetRules
{
	public BattleTank_UnrealTarget(TargetInfo Target)
	{
		Type = TargetType.Game;
	}

	//
	// TargetRules interface.
	//

	public override void SetupBinaries(
		TargetInfo Target,
		ref List<UEBuildBinaryConfiguration> OutBuildBinaryConfigurations,
		ref List<string> OutExtraModuleNames
		)
	{
		OutExtraModuleNames.AddRange( new string[] { "BattleTank_Unreal" } );
	}
}
