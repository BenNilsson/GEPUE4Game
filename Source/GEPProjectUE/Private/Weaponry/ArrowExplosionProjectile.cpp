// Fill out your copyright notice in the Description page of Project Settings.


#include "Weaponry/ArrowExplosionProjectile.h"

#include "Kismet/GameplayStatics.h"

AArrowExplosionProjectile::AArrowExplosionProjectile() : Super()
{
	
}

void AArrowExplosionProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComponent != nullptr) && !HasHit)
	{
		// Disable arrow damage
		HasHit = true;

		// Deal Damage
		UGameplayStatics::ApplyDamage(OtherActor, 10.0f, this->GetInstigatorController(), this,
        TSubclassOf<UDamageType>(UDamageType::StaticClass()));
	}	
}
