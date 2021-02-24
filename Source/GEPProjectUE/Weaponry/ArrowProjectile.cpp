// Fill out your copyright notice in the Description page of Project Settings.


#include "ArrowProjectile.h"

#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
AArrowProjectile::AArrowProjectile()
{
	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	CollisionComponent->InitBoxExtent(FVector(2, 1, 1));
	CollisionComponent->BodyInstance.SetCollisionProfileName("Projectile");
	// Sets up a notification for when the arrow hits something
	CollisionComponent->OnComponentHit.AddDynamic(this, &AArrowProjectile::OnHit);

	// Stop player from walking on the arrow
	CollisionComponent->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComponent->CanCharacterStepUpOn = ECB_No;

	// Set as Root
	RootComponent = CollisionComponent;

	// Projectile Movement
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->UpdatedComponent = CollisionComponent; // Sets what to move
	ProjectileMovementComponent->InitialSpeed = 3000.0f;
	ProjectileMovementComponent->MaxSpeed = 3000.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true; // Rotate towards velocity, essential for an arrow
	ProjectileMovementComponent->bShouldBounce = true;

	// Lifespan
	InitialLifeSpan = 10.0f;
}

void AArrowProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
                             FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComponent != nullptr) && OtherComponent->IsSimulatingPhysics())
	{
		OtherComponent->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
		// TODO - Apply Damage
	}	
}

