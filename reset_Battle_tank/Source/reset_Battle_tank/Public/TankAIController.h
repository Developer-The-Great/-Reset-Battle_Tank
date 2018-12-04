// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */

class UTankAimingComponent;
UCLASS()
class RESET_BATTLE_TANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()


	virtual void BeginPlay() override;



	void Tick(float DeltaTime) override;
	

private:
	float AcceptanceRadius = 1000;
	
	UTankAimingComponent * TankAimingComponent = nullptr;


};
