// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ArrowProjectile.generated.h"

UCLASS(Config = Game)
class GEPPROJECTUE_API AArrowProjectile : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = "Projectile")
	class UBoxComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjectileMovementComponent;

public:
	// Sets default values for this actor's properties
	AArrowProjectile();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	FORCEINLINE class UBoxComponent* GetCollisionComp() const { return CollisionComponent; }

	FORCEINLINE class UProjectileMovementComponent* GetProjectileComponent() const { return ProjectileMovementComponent; }
};
