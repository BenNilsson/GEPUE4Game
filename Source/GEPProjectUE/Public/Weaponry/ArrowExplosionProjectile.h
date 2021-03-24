// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weaponry/ArrowProjectile.h"
#include "ArrowExplosionProjectile.generated.h"

/**
 * 
 */
UCLASS()
class GEPPROJECTUE_API AArrowExplosionProjectile : public AArrowProjectile
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ExplosionArrow")
	float DamageRadius;

public:
	AArrowExplosionProjectile();

	virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) override;
};
