// Copyright Yurgen Hohmeyer 2017

using UnrealBuildTool;
using System.Collections.Generic;

public class BattleTank_UnrealEditorTarget : TargetRules
{
	public BattleTank_UnrealEditorTarget(TargetInfo Target)
	{
		Type = TargetType.Editor;
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
