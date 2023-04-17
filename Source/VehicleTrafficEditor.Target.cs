// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class VehicleTrafficEditorTarget : TargetRules
{
	public VehicleTrafficEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("VehicleTraffic");
		ExtraModuleNames.Add("VehicleTrafficEditor");
	}
}
