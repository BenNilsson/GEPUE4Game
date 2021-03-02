// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GEPProjectUE/Public/Interfaces/Fireable.h"
#include "GEPProjectUE/Public/Interfaces/Weaponable.h"


#include "WeaponBase.generated.h"


enum class EWeapon_Combat_Type;

UCLASS()
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
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool Fire();
	virtual bool Fire_Implementation() override;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool FireReleased();
	virtual bool FireReleased_Implementation() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	EWeapon_Combat_Type GetWeaponType();
	virtual EWeapon_Combat_Type GetWeaponType_Implementation() override;
};
