// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "ArrowProjectile.h"
#include "WeaponBase.h"
#include "Interfaces/GetWeaponBow.h"

#include "WeaponBow.generated.h"

UCLASS(BlueprintType, Blueprintable)
class GEPPROJECTUE_API AWeaponBow : public AWeaponBase, public IGetWeaponBow
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AWeaponBow();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AArrowProjectile> ArrowProjectile;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	class UArrowComponent* ArrowComponent;
	
	virtual bool Fire_Implementation() override;
	virtual bool FireReleased_Implementation() override;
	virtual bool FireHeld_Implementation() override;

	FORCEINLINE class UArrowComponent* GetArrowComponent() const { return ArrowComponent;}

	virtual AWeaponBow* GetWeaponBow_Implementation() override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
