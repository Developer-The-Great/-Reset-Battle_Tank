// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class RESET_BATTLE_TANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
		UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTankThrottle(float Throttle);


private:
	UPROPERTY(EditDefaultsOnly)
	float MaxDrivingForce = 400000;
	
	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UTankTrack();
};
