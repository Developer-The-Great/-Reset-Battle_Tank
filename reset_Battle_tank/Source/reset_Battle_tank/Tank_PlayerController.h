// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/PlayerController.h"
#include "Tank_PlayerController.generated.h"

/**
 * 
 */

class UTankAimingComponent;
UCLASS()
class RESET_BATTLE_TANK_API ATank_PlayerController : public APlayerController
{
	GENERATED_BODY()
protected:


	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent *AimingRef);
public:	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	void AimTowardsCrosshair();
		
	bool GetSightRayHitLocation(FVector &HitLocation) const;

	bool GetLookDirection(FVector2D ScreenLoc, FVector &CamWorldDirection) const;

	bool GetLookVectorHitLocation(FVector &HitLocation, FVector CamWorldDirection) const;


private:
	UFUNCTION()


	void SetPawn(APawn * InPawn) override;
	UPROPERTY(EditDefaultsOnly)
	float CrossHairXLocation = 0.5;
	UPROPERTY(EditDefaultsOnly)
	float CrossHairYLocation = 0.3333;

	float LineTraceRange = 100000;
	
	UTankAimingComponent * TankAimingComponent = nullptr;

	UFUNCTION()
	void OnTankDeath();
	
	
};
