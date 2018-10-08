// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "Tank_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class RESET_BATTLE_TANK_API ATank_PlayerController : public APlayerController
{
	GENERATED_BODY()

		ATank * GetPlayerController() const;
		
		void BeginPlay() override;
	
	
};
