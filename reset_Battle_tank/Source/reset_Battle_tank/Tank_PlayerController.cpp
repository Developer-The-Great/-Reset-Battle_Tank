// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank_PlayerController.h"
#include "Tank.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"


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
	if (GetSightRayHitLocation(HitLocation)) 
	{
		//UE_LOG(LogTemp, Warning, TEXT("Aiming! End: %s"), *HitLocation.ToString());
		GetControlledTank()->AimAt(HitLocation);
	}
	

}

bool ATank_PlayerController::GetSightRayHitLocation(FVector & HitLocation) const
{
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	//Find CrossHair Position
	FVector2D ScreenLoc =  FVector2D(ViewportSizeX*CrossHairXLocation, ViewportSizeY*CrossHairYLocation);
	
	
	FVector CamWorldDirection;
	//Find Camera Direction
	if (GetLookDirection(ScreenLoc, CamWorldDirection)) 
	{	
		
		bool bLookDirection = GetLookVectorHitLocation(HitLocation, CamWorldDirection);
		return bLookDirection;
	}
	
	return true;
}

bool ATank_PlayerController::GetLookDirection(FVector2D ScreenLoc, FVector & CamWorldDirection) const
{
	FVector CamWorldLocation;
	return DeprojectScreenPositionToWorld(ScreenLoc.X, ScreenLoc.Y, CamWorldLocation, CamWorldDirection);
	
}

bool ATank_PlayerController::GetLookVectorHitLocation(FVector &HitLocation,FVector CamWorldDirection) const
{	
	
	FHitResult HitResult;
	auto StartLoc = PlayerCameraManager->GetCameraLocation();
	auto EndLoc = StartLoc + (CamWorldDirection * LineTraceRange);
	bool bHitResultFound = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLoc,
		EndLoc,
		ECollisionChannel::ECC_Visibility
	);
	if(bHitResultFound)
	{
		HitLocation = HitResult.Location;
		return true;

	}
	HitLocation = FVector(0);
	return false;

	
}
