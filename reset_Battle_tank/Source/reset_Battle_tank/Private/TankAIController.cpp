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
	

}

ATank * ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void ATankAIController::Tick(float DeltaTime)
{

	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto AITank = Cast<ATank>(GetPawn());

	if (PlayerTank)
	{
		MoveToActor(PlayerTank, AcceptanceRadius);
		AITank->AimAt(PlayerTank->GetActorLocation());
		//AITank->Fire();
	}

	

}

void ATankAIController::AimAt(FVector HitLocation)
{

	
	GetAITank()->AimAt(HitLocation);
	auto AITankName = GetAITank()->GetName();

	
}
