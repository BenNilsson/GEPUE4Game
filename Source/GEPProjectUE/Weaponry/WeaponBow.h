// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "ArrowProjectile.h"
#include "WeaponBase.h"
#include "WeaponBow.generated.h"

UCLASS()
class GEPPROJECTUE_API AWeaponBow : public AWeaponBase
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly)
	TSubclassOf<AArrowProjectile> ArrowProjectile;

	UPROPERTY(VisibleDefaultsOnly)
	class UArrowComponent* ArrowComponent;
	
public:
	// Sets default values for this actor's properties
	AWeaponBow();

	virtual bool Fire_Implementation() override;
	virtual bool FireReleased_Implementation() override;
	virtual bool FireHeld_Implementation() override;

	FORCEINLINE class UArrowComponent* GetArrowComponent() const { return ArrowComponent;}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
