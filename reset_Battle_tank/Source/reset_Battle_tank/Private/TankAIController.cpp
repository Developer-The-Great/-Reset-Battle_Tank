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

void ATankAIController::Tick(float DeltaTime)
{
	if (!GetPlayerTank())
	{
		return;

	}

	AimAt(GetPlayerTank()->GetActorLocation());

}

void ATankAIController::AimAt(FVector HitLocation)
{

	
	GetAITank()->AimAt(HitLocation);
	auto AITankName = GetAITank()->GetName();

	UE_LOG(LogTemp, Warning, TEXT("AI_Tank: %s aiming at %s"), *AITankName, *HitLocation.ToString());
}
