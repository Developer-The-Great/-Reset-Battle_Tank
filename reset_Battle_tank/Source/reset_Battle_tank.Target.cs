// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class reset_Battle_tankTarget : TargetRules
{
	public reset_Battle_tankTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "reset_Battle_tank" } );
	}
}
