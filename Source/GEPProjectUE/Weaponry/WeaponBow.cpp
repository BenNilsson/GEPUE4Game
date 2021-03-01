// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBow.h"

#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
AWeaponBow::AWeaponBow()
{
	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow Spawn Location"));
	ArrowComponent->SetupAttachment(RootSceneComponent);

	EWeaponType = Ranged;
}

// Fire first pressed
bool AWeaponBow::Fire_Implementation()
{
	return true;
}

// Fire released
bool AWeaponBow::FireReleased_Implementation()
{
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

	FVector ArrowDirection = Start + (Forward * 2000);
	FRotator SpawnRotation = UKismetMathLibrary::FindLookAtRotation(SpawnLoc, ArrowDirection);
	
	// Line trace from camera outwards
	if (World->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility))
		SpawnRotation = UKismetMathLibrary::FindLookAtRotation(SpawnLoc, Hit.ImpactPoint);
	
	World->SpawnActor<AArrowProjectile>(ArrowProjectile, SpawnLoc, SpawnRotation, ActorSpawnParameters);
	return true;
}

// Fire held down
bool AWeaponBow::FireHeld_Implementation()
{
	return true;
}

// Called when the game starts or when spawned
void AWeaponBow::BeginPlay()
{
	Super::BeginPlay();
	
}

