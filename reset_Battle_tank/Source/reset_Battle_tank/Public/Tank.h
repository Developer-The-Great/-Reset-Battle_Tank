// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "Tank.generated.h"

UCLASS()
class RESET_BATTLE_TANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);
	FTankDelegate OnTankDeath;
	// Sets default values for this pawn's properties
	ATank();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;

	//UFUNCTION(BlueprintCallable, Category = Setup)
	//void SetBarrelReference(UTankBarrel * BarrelToSet);

	//UFUNCTION(BlueprintCallable, Category = Setup)
	//void SetTurretReference(UTankTurret * TurretToSet);

	UFUNCTION(BlueprintPure, category = "Health")
	float GetHealthPercent() const;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:


	UPROPERTY(EditDefaultsOnly)
	int32 StartingHealth = 20;
	UPROPERTY(VisibleAnywhere)
	int32 CurrentHealth = StartingHealth;


};
