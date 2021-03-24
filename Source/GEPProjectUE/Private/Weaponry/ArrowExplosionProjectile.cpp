// Fill out your copyright notice in the Description page of Project Settings.


#include "Weaponry/ArrowExplosionProjectile.h"

#include "Kismet/GameplayStatics.h"

AArrowExplosionProjectile::AArrowExplosionProjectile() : Super()
{
	DamageRadius = 500;
}

void AArrowExplosionProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (HasHit)
		return;
	
	// Disable arrow damage
	HasHit = true;

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetOwner());
	
	// Deal Damage
	UGameplayStatics::ApplyRadialDamage(GetWorld(), 50, GetActorLocation(), DamageRadius, TSubclassOf<UDamageType>(UDamageType::StaticClass()),
    ActorsToIgnore, this, this->GetInstigatorController(), true);
		
}
