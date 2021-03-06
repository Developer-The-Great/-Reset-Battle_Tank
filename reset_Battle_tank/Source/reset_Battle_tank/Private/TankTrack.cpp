// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Engine/World.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
	//
	//OnComponentHit
}

void UTankTrack::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	
	//UE_LOG(LogTemp, Warning, TEXT("HIT"));
	
	DriveTrack();
	ApplySidewaysForce();
	CurrentThrottle = 0;
	
}
void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);

}



void UTankTrack::ApplySidewaysForce()
{
	//UE_LOG(LogTemp, Warning, TEXT("TICK"));
	//calculate slippage speed
	float DeltaTime = GetWorld()->GetDeltaSeconds();
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	//work out acc required for this frame to correct 
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();
	//apply said acceleration to tank
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());

	auto CorrectionForce = TankRoot->GetMass() * CorrectionAcceleration / 2;

	TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::SetTankThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1.5f, 1.5f);
	

}
void UTankTrack::DriveTrack()
{
	auto Name = GetName();

	auto Force = GetForwardVector() * MaxDrivingForce * CurrentThrottle;
	auto ForceLocation = GetComponentLocation();

	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	TankRoot->AddForceAtLocation(Force, ForceLocation);
}


