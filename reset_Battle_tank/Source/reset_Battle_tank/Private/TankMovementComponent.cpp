// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!LeftTrack || !RightTrack)
	{
		return;
	}
	//UE_LOG(LogTemp,Warning,TEXT("Triggered F/B"))
	LeftTrack->SetTankThrottle(Throw);
	RightTrack->SetTankThrottle(Throw);

}

void UTankMovementComponent::IntendTurn(float Throw)
{
	if (!LeftTrack || !RightTrack)
	{
		return;
	}
	
	if (Throw > 0) 
	{
		UE_LOG(LogTemp, Warning, TEXT("right"))
		
	}
	else if (Throw < 0) 
	{
		UE_LOG(LogTemp, Warning, TEXT("left"))
	
	}
	LeftTrack->SetTankThrottle(-Throw);
	RightTrack->SetTankThrottle(Throw);

}

void UTankMovementComponent::Initialize(UTankTrack * LeftTrackToSet, UTankTrack * RightTrackToSet)
{
	if(!LeftTrackToSet && !RightTrackToSet)
	{
		return;
	}
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	auto TankName = GetOwner()->GetName();

	

	auto IntendedDirection = MoveVelocity.GetSafeNormal();
	auto TankDirection = GetOwner()->GetActorForwardVector().GetSafeNormal();
	float ThrowRequired = FVector::DotProduct(IntendedDirection, TankDirection);
	UE_LOG(LogTemp, Warning, TEXT("DotProduct: %f"), ThrowRequired)
	IntendMoveForward(ThrowRequired);


}


