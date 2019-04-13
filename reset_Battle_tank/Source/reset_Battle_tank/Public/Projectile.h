// Fill out your copyright notice in the Description page of Project Settings.
//
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"


#include "Projectile.generated.h"

class UProjectileMovementComponent;
class UParticleSystemComponent;
class URadialForceComponent;
UCLASS()
class RESET_BATTLE_TANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();
	void LaunchProjectile(float LaunchSpeed);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

private:	
	// Called every frame
	UFUNCTION()
	void OnHit( AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

	void OnTimerExpire();

	UProjectileMovementComponent * Projectile;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* CollisionMesh = nullptr;
	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent *LaunchBlast = nullptr;

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent *ImpactBlast = nullptr;

	UPROPERTY(VisibleAnywhere)
	URadialForceComponent* RadialForce = nullptr;

	UPROPERTY(EditDefaultsOnly)
	float DestroyDelay = 10;
	UPROPERTY(EditDefaultsOnly)
	float ProjectileDamage = 10.f;

	
	
};
