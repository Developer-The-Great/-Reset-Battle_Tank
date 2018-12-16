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
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);


	virtual void BeginPlay() override;
	//void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void ApplySidewaysForce();
	UTankTrack();

	float CurrentThrottle = 0;

	void DriveTrack();
};
