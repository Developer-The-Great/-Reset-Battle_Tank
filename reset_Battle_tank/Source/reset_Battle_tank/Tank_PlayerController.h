// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/PlayerController.h"
#include "Tank_PlayerController.generated.h"

/**
 * 
 */
class ATank;
UCLASS()
class RESET_BATTLE_TANK_API ATank_PlayerController : public APlayerController
{
	GENERATED_BODY()

	ATank * GetControlledTank() const;
		
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	void AimTowardsCrosshair();
		
	bool GetSightRayHitLocation(FVector &HitLocation) const;

	bool GetLookDirection(FVector2D ScreenLoc, FVector &CamWorldDirection) const;

	bool GetLookVectorHitLocation(FVector &HitLocation, FVector CamWorldDirection) const;
private:
	UPROPERTY(EditDefaultsOnly)
	float CrossHairXLocation = 0.5;
	UPROPERTY(EditDefaultsOnly)
	float CrossHairYLocation = 0.3333;

	float LineTraceRange = 100000;
	
	
	
};
