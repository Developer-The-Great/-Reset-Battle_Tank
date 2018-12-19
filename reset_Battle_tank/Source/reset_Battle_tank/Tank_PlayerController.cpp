// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank_PlayerController.h"
#include "TankAimingComponent.h"

#include "Engine/World.h"
#include "GameFramework/PlayerController.h"


void ATank_PlayerController::BeginPlay() 
{
	
	Super::BeginPlay();
	

	
	TankAimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	FoundAimingComponent(TankAimingComponent);
}

void ATank_PlayerController::Tick(float DeltaTime)
{
	AimTowardsCrosshair();
}

void ATank_PlayerController::AimTowardsCrosshair()
{
	TankAimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!TankAimingComponent) { return; }

	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation)) 
	{
		//UE_LOG(LogTemp, Warning, TEXT("Aiming! End: %s"), *HitLocation.ToString());
		TankAimingComponent->AimAt(HitLocation);
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
	
	return false;
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
