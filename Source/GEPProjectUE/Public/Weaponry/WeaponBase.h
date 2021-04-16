// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Fireable.h"
#include "Interfaces/Weaponable.h"
#include "WeaponBase.generated.h"

enum class EWeapon_Combat_Type;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWeaponFireEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWeaponFireHeldEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWeaponFireReleasedEvent);

UCLASS(BlueprintType, Blueprintable)
class GEPPROJECTUE_API AWeaponBase : public AActor, public IFireable, public IWeaponable
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

	virtual bool Fire_Implementation() override;
	virtual bool FireReleased_Implementation() override;
	virtual bool FireHeld_Implementation() override;

	UPROPERTY(BlueprintAssignable, Category="Weapon Events")
	FWeaponFireEvent OnWeaponFiredEvent;
	UPROPERTY(BlueprintAssignable, Category="Weapon Events")
	FWeaponFireHeldEvent OnWeaponFireHeldEvent;
	UPROPERTY(BlueprintAssignable, Category="Weapon Events")
	FWeaponFireReleasedEvent OnWeaponFiredReleasedEvent;
	

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	EWeapon_Combat_Type GetWeaponType();
	virtual EWeapon_Combat_Type GetWeaponType_Implementation() override;
};
