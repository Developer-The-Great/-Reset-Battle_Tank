// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank_PlayerController.h"

ATank * ATank_PlayerController::GetPlayerController() const
{
	return Cast<ATank>(GetPawn());
}
void ATank_PlayerController::BeginPlay() 
{
	
	Super::BeginPlay();
	auto PlayerController = GetPlayerController();
	if (PlayerController) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Possesing %s"),*PlayerController->GetName());
	}
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank Not Found!"));
	
	}
	
	
}
