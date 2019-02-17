// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "Tank.h"
#include "../Public/TankAIController.h"


void ATankAIController::BeginPlay() 
{
	Super::BeginPlay();
	
	TankAimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
}


void ATankAIController::Tick(float DeltaTime)
{

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto AITank =GetPawn();

	auto TankAimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(TankAimingComponent) || !ensure(PlayerTank))
	{
		return;
	
	}


	MoveToActor(PlayerTank, AcceptanceRadius);
	TankAimingComponent->AimAt(PlayerTank->GetActorLocation());
	if(TankAimingComponent->GetFiringState() == EFiringStatus::Locked)
	{
		TankAimingComponent->Fire();
	
	}
	
	

	

}

void ATankAIController::OnTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("TANK DEATH"));
}

void ATankAIController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if(InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);

		if(!ensure(PossessedTank))
		{
			return;
		}

		PossessedTank->OnTankDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
	
	}
}

//void ATankAIController::AimAt(FVector HitLocation)
//{
//
//	
//	GetAITank()->AimAt(HitLocation);
//	auto AITankName = GetAITank()->GetName();
//
//	
//}
