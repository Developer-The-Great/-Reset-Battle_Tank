// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "../Public/TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}



void UTankAimingComponent::AimAt(FVector HitLocation,float LaunchSpeed)
{
	if (!Barrel) { return; }
	
	FVector TossVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool bAimSolutionFound = UGameplayStatics::SuggestProjectileVelocity(this, TossVelocity, StartLocation, HitLocation, LaunchSpeed, false, 0.0f, 0.0f, ESuggestProjVelocityTraceOption::DoNotTrace);
	if (bAimSolutionFound)
	{
		auto TankName = GetOwner()->GetName();
		auto AimDirection = TossVelocity.GetSafeNormal();
		//UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s"), *TankName, *AimDirection.ToString());
		MoveBarrelTowards(AimDirection);
		
	
	}
	
	

	
	
		
}

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent *BarrelToSet)
{
	Barrel = BarrelToSet;
}
void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	auto CurrentRotation = Barrel->GetForwardVector().Rotation();
	auto NeededRotation = AimDirection.Rotation();
	auto DeltaRotation = NeededRotation - CurrentRotation;
	UE_LOG(LogTemp,Warning,TEXT("need rotation: %s"),*DeltaRotation.ToString())

}

