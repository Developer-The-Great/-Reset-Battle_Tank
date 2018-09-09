// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class reset_Battle_tankEditorTarget : TargetRules
{
	public reset_Battle_tankEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "reset_Battle_tank" } );
	}
}
