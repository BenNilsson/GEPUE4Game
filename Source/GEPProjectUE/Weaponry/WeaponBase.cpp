// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"


// Sets default values
AWeaponBase::AWeaponBase()
{
	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Weapon Root"));
	RootSceneComponent->SetupAttachment(RootComponent);

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon Skeletal Mesh"));
	WeaponMesh->SetupAttachment(RootSceneComponent);
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

bool AWeaponBase::Fire_Implementation()
{
	return true;
}

bool AWeaponBase::FireReleased_Implementation()
{
	return true;
}

bool AWeaponBase::FireHeld_Implementation()
{
	return true;
}

