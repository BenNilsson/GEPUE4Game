// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GEPProjectUE/Interfaces/Fireable.h"

#include "WeaponBase.generated.h"

UENUM(BlueprintType)
enum EWeapon_Combat_Type
{
	None = 0 		UMETA(DisplayName = "None"),
    Melee = 1		UMETA(DisplayName = "Melee"),
    Ranged = 2	UMETA(DisplayName = "Ranged"),
};



UCLASS()
class GEPPROJECTUE_API AWeaponBase : public AActor, public IFireable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeaponBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/* ROOT SCENE COMPONENT */
	UPROPERTY(VisibleDefaultsOnly)
	class USceneComponent* RootSceneComponent;

	/* MESH */
	UPROPERTY(VisibleDefaultsOnly)
	class USkeletalMeshComponent* WeaponMesh;

	/* Anim Montage */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controller Settings")
	class UAnimMontage* WeaponAnimMontage;

	/* COMBAT STATE */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TEnumAsByte<EWeapon_Combat_Type> EWeaponType;
	
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool Fire();
	virtual bool Fire_Implementation() override;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool FireReleased();
	virtual bool FireReleased_Implementation() override;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool FireHeld();
	virtual bool FireHeld_Implementation() override;
};
