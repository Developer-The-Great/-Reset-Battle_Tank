// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnPoint.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

// Sets default values for this component's properties
USpawnPoint::USpawnPoint()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	auto Actor = GetWorld()->SpawnActorDeferred<AActor>(SpawnClass,GetComponentTransform(),nullptr,nullptr);
	if (!Actor) 
	{
		UE_LOG(LogTemp, Warning, TEXT("No Actor attached to spawn point"));
		return; 
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT(" Actor succesfully attached to spawn point"));
	}
	Actor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
	UGameplayStatics::FinishSpawningActor(Actor, GetComponentTransform());
	
	// ...
	
}


// Called every frame
void USpawnPoint::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

