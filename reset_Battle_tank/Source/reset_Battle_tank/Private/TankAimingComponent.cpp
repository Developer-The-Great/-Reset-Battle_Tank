// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "../Public/TankAimingComponent.h"
#include "Engine/World.h"
#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTankAimingComponent::Initialize(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	LastFireTime = FPlatformTime::Seconds();
	// ...
}


void UTankAimingComponent::Fire()
{
	if (!ensure(Barrel)) { return; }
	else if (!ensure(ProjectileBlueprint)) { return; }
	
	
	
	if(FiringStatus == EFiringStatus::Aiming || FiringStatus == EFiringStatus::Locked)
	{
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketTransform(FName("Projectile")));
		

		
		//UE_LOG(LogTemp, Warning, TEXT("%s"), *X.ToString());

		

		Amno--;
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
		UE_LOG(LogTemp, Warning, TEXT("FIRE"));
	}
	
	//bool bIsBarrelMoving = FVector::Equals(CurrentBarrelRot, AimDirection,0.01f);
	

	
}

EFiringStatus UTankAimingComponent::GetFiringState() const
{
	return FiringStatus;
}

int32 UTankAimingComponent::GetAmno() const
{
	return Amno;
}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//UE_LOG(LogTemp, Warning, TEXT("Amno: %i"), Amno);
	

	auto CurrentBarrelRot = Barrel->GetForwardVector();
	//reloading
	if(Amno <= 0)
	{
		FiringStatus = EFiringStatus::OutOfAmno;

	
	}
	else if (FPlatformTime::Seconds() - LastFireTime < ReloadTimeSeconds)
	{
		FiringStatus = EFiringStatus::Realoading;
		//UE_LOG(LogTemp, Warning, TEXT("RELOADING"));
	}
	//Aiming
	else if (!CurrentBarrelRot.Equals(AimDirection,0.02))
	{
		FiringStatus = EFiringStatus::Aiming;
		//UE_LOG(LogTemp, Warning, TEXT("Aiming"));
	}
	else 
	{
		//UE_LOG(LogTemp, Warning, TEXT("Locked"));
		FiringStatus = EFiringStatus::Locked;
	
	}

	// ...
}



void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel)) { 
		UE_LOG(LogTemp, Warning, TEXT("aim at no tick!"));
		return; 
		
	}
	
	FVector TossVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	
	//gives out the direction to hit an object from StartLocation to HitLocation with a speed of LaunchSpeed
	bool bAimSolutionFound = UGameplayStatics::SuggestProjectileVelocity(
		this, 
		TossVelocity, 
		StartLocation, 
		HitLocation, 
		LaunchSpeed, 
		false, 
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace);

	//if its not out of range
	if (bAimSolutionFound)
	{
		auto TankName = GetOwner()->GetName();
		AimDirection = TossVelocity.GetSafeNormal();
		//AimDirection = &Direction;
		//UE_LOG(LogTemp, Warning, TEXT("solution AIM DIRECTION:%s"),*AimDirection.ToString());
		MoveBarrelTowards(AimDirection);
	}
	else 
	{
		//UE_LOG(LogTemp, Warning, TEXT("no solution"));
	
	}

}




void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(Barrel && Turret)) 
	{	
		return; 
	}
	auto CurrentRotation = Barrel->GetForwardVector().Rotation();
	auto NeededRotation = AimDirection.Rotation();
	auto DeltaRotation = NeededRotation - CurrentRotation;
	if (FMath::Abs(DeltaRotation.Yaw) < 180) 
	{
		Turret->Rotate(DeltaRotation.Yaw);
	
	}
	else 
	{
		Turret->Rotate(-DeltaRotation.Yaw);
	
	}
	Barrel->Elevate(DeltaRotation.Pitch);
	

}

