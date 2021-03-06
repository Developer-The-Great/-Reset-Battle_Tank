// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick =false;

	Projectile = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileMovement"));
	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("CollisionMesh"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(false);


	LaunchBlast = CreateDefaultSubobject< UParticleSystemComponent>(FName("LaunchBlast"));
	LaunchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	ImpactBlast = CreateDefaultSubobject< UParticleSystemComponent>(FName("ImpactBlast"));
	ImpactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	Projectile->bAutoActivate = false;
	ImpactBlast->bAutoActivate = false;

	RadialForce = CreateDefaultSubobject<URadialForceComponent>(FName("RadialForce"));
	RadialForce->bAutoActivate = false;
	RadialForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

void AProjectile::LaunchProjectile(float LaunchSpeed)
{
	Projectile->SetVelocityInLocalSpace(FVector::ForwardVector*LaunchSpeed);
	Projectile->Activate();
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	OnActorHit.AddDynamic(this, &AProjectile::OnHit);
}

void AProjectile::OnHit( AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	
	
	
	//UE_LOG(LogTemp, Warning, TEXT("HITNAME: %s"), *Name);
	LaunchBlast->Deactivate();
	ImpactBlast->Activate();
	UE_LOG(LogTemp, Warning, TEXT("HIT"));
	RadialForce->FireImpulse();
	//RadialForce->Deactivate();

	SetRootComponent(ImpactBlast);
	CollisionMesh->DestroyComponent();

	UGameplayStatics::ApplyRadialDamage
	(
		this,
		ProjectileDamage,
		GetActorLocation(),
		RadialForce->Radius,
		UDamageType::StaticClass(),
		TArray<AActor*>()
	);
	//GetWorld()->GetTimerManager().SetTimer()
	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(Handle, this, &AProjectile::OnTimerExpire,DestroyDelay,false);

	
}
void AProjectile::OnTimerExpire()
{
	Destroy();


}
// Called every frame


