// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Engine/World.h"

void UTankTurret::Elevate(float RelativeSpeed) 
{
	
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);

	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->GetTimeSeconds();

	auto NewRotation = RelativeRotation.Yaw + RotationChange;
	
	SetRelativeRotation(FRotator(RelativeRotation.Pitch, NewRotation, RelativeRotation.Roll));

}


