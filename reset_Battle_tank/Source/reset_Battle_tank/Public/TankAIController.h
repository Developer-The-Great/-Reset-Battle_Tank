// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class RESET_BATTLE_TANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

	ATank* GetAITank() const;

	virtual void BeginPlay() override;

	ATank* GetPlayerTank() const;

	void Tick(float DeltaTime) override;
	
	virtual void AimAt(FVector HitLocation);
private:
	float AcceptanceRadius = 1000;
	
};
