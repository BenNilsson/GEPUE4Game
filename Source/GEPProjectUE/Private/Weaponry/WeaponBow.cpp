// Fill out your copyright notice in the Description page of Project Settings.


#include "Weaponry/WeaponBow.h"

#include "Components/ArrowComponent.h"
#include "WeaponCombatTypeEnum.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AWeaponBow::AWeaponBow()
{
	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow Spawn Location"));
	ArrowComponent->SetupAttachment(RootSceneComponent);

	EWeaponType = EWeapon_Combat_Type::Ranged;
}

bool AWeaponBow::FireHeld_Implementation()
{
	OnWeaponFireHeldEvent.Broadcast();
	return true;
}

// Fire first pressed
bool AWeaponBow::Fire_Implementation()
{
	OnWeaponFiredEvent.Broadcast();
	return true;
}

// Fire released
bool AWeaponBow::FireReleased_Implementation()
{
	/*
	UWorld* const World = GetWorld();

	if (!World && ArrowProjectile == nullptr) return false;

	FVector const SpawnLoc = ArrowComponent->GetComponentLocation();
	
	FHitResult Hit(ForceInit);
	FVector Start = UGameplayStatics::GetPlayerController(World, 0)->PlayerCameraManager->GetCameraLocation();
	FVector Forward = UGameplayStatics::GetPlayerController(World, 0)->PlayerCameraManager->GetActorForwardVector();
	FVector End = Start + (Forward * 100000.0f);
	
	FActorSpawnParameters ActorSpawnParameters;
	ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	AActor* ParentActor = GetParentActor();
	ActorSpawnParameters.Owner = ParentActor;

	FVector ArrowDirection = Start + (Forward * 3000);
	FRotator SpawnRotation = UKismetMathLibrary::FindLookAtRotation(SpawnLoc, ArrowDirection);
	
	// Line trace from camera outwards
	if (World->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility))
		SpawnRotation = UKismetMathLibrary::FindLookAtRotation(SpawnLoc, Hit.ImpactPoint);
	
	World->SpawnActor<AArrowProjectile>(ArrowProjectile, SpawnLoc, SpawnRotation, ActorSpawnParameters);
	return true;
	*/
	OnWeaponFiredReleasedEvent.Broadcast();
	return true;
}

AWeaponBow* AWeaponBow::GetWeaponBow_Implementation()
{
	return this;
}

// Called when the game starts or when spawned
void AWeaponBow::BeginPlay()
{
	Super::BeginPlay();
	
}

