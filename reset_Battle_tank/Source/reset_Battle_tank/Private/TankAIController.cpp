// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "../Public/TankAIController.h"

ATank * ATankAIController::GetAITank() const
{
	return Cast<ATank>(GetPawn());
}
void ATankAIController::BeginPlay() 
{
	Super::BeginPlay();
	auto AITank = GetAITank();
	if (AITank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AITankController possessing: %s"), *AITank->GetName());

	}

	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AITankController not possessing"));
	
	}

	auto PlayerTank = GetPlayerTank();
	if (PlayerTank) 
	{
		UE_LOG(LogTemp, Warning, TEXT("%s has found player tank: %s"), *AITank->GetName(),*PlayerTank->GetName());


	}
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("AITankController cannot find player tank!"));
	}


}

ATank * ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}
