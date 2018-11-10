// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;
/**
 * 
 */
UCLASS(ClassGroup = (Custom),meta = (BlueprintSpawnableComponent))
class RESET_BATTLE_TANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	UFUNCTION(BlueprintCallable, Category = Setup)
	void IntendMoveForward(float Throw);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void IntendTurn(float Throw);
		
	UFUNCTION(BlueprintCallable, Category = Input)
	void Initialize(UTankTrack * LeftTrackToSet,UTankTrack* RightTrackToSet);
	
private:
	UTankTrack * LeftTrack = nullptr;
	UTankTrack * RightTrack = nullptr;
	UPROPERTY(EditDefaultsOnly)
	float ForwardDrivingForce = 400000;
	
};
