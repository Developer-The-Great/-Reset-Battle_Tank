// Fill out your copyright notice in the Description page of Project Settings.

#include "WheeledSpring.h"
# include "Components/StaticMeshComponent.h"

// Sets default values
AWheeledSpring::AWheeledSpring()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	wheel = CreateAbstractDefaultSubobject<UStaticMeshComponent>(FName("Wheel"));
	physicsConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("PhysicsConstraint"));

	bool Set = SetRootComponent(physicsConstraint);
	wheel->SetupAttachment(physicsConstraint);
	


	if (Set)
	{
		UE_LOG(LogTemp, Warning, TEXT("WHEELED SPRING"));

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ROOT COMPONENT NOT SET"));
	}



}

// Called when the game starts or when spawned
void AWheeledSpring::BeginPlay()
{
	Super::BeginPlay();
	auto Actor = GetAttachParentActor();

	if (!Actor)
	{
		UE_LOG(LogTemp, Warning, TEXT("NO PARENT"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ACTOR: %s"), *Actor->GetName());
	}
}

// Called every frame
void AWheeledSpring::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

