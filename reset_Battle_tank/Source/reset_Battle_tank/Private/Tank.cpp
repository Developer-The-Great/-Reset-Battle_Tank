// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	UE_LOG(LogTemp, Warning, TEXT("DONKEY: %s Constructor cpp"), *GetName());
	//TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));

	
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("DONKEY: %s BeginPLay cpp"), *GetName());
	
}




//void ATank::SetBarrelReference(UTankBarrel * BarrelToSet)
//{
//	TankAimingComponent->SetBarrelReference(BarrelToSet);
//	Barrel = BarrelToSet;
//}
//
//void ATank::SetTurretReference(UTankTurret * TurretToSet)
//{
//	TankAimingComponent->SetTurretReference(TurretToSet);
//}

void ATank::Fire()
{	
	if (!ensure(Barrel)) { return; }
	//UE_LOG(LogTemp, Warning, TEXT("Firing"));
	bool IsReloaded = (FPlatformTime::Seconds() - LastFireTime > ReloadTimeSeconds);
	if (IsReloaded)
	{
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketTransform(FName("Projectile")));

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}

	
	

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
void ATank::AimAt(FVector HitLocation) 
{	
	if (!ensure(TankAimingComponent)) { return; }
	TankAimingComponent->AimAt(HitLocation,LaunchSpeed);
	

}

