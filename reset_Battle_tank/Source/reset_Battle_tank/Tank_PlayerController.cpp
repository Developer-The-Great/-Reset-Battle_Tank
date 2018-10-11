// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank_PlayerController.h"
using OUT;

ATank * ATank_PlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
void ATank_PlayerController::BeginPlay() 
{
	
	Super::BeginPlay();
	auto PlayerController = GetControlledTank();
	if (PlayerController) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Possesing %s"),*PlayerController->GetName());
	}
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank Not Found!"));
	
	}
	
	
}

void ATank_PlayerController::Tick(float DeltaTime)
{
	AimTowardsCrosshair();
}

void ATank_PlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation;
	if (GetSightRayHitLocation(OUT HitLocation)) 
	{
	
	
	
	}
	

}

bool ATank_PlayerController::GetSightRayHitLocation(FVector & HitLocation) const
{
	return false;
}
