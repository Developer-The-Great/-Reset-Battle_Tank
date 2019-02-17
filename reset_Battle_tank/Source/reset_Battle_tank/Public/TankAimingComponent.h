// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringStatus : uint8
{
	Locked,
	Aiming,
	Realoading,
	OutOfAmno
};
class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )

class RESET_BATTLE_TANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();
	void AimAt(FVector HitLocation);

	/*void SetBarrelReference(UTankBarrel *BarrelToSet);

	void SetTurretReference(UTankTurret *TurretToSet);*/

	UFUNCTION(BlueprintCallable, Category = Input)
	void Initialize(UTankBarrel *BarrelToSet, UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();

	UFUNCTION(BlueprintCallable, Category = Firing)
	EFiringStatus GetFiringState() const;

	UFUNCTION(BlueprintCallable, Category = Firing)
	int32 GetAmno() const;

	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringStatus FiringStatus = EFiringStatus::Realoading;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile>  ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Amno")
	int32 Amno = 5;

private:	
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	


	UTankBarrel * Barrel = nullptr;
	UTankTurret * Turret = nullptr;

	void MoveBarrelTowards(FVector AimDirection);

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 10000;
	
	double LastFireTime = 0;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeSeconds = 3;

	//FVector* AimDirection = nullptr;
	FVector AimDirection;

	
};
