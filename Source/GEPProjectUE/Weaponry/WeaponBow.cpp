// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBow.h"

#include "Components/ArrowComponent.h"


// Sets default values
AWeaponBow::AWeaponBow()
{
	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow Spawn Location"));
	ArrowComponent->SetupAttachment(RootSceneComponent);
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
	FRotator const SpawnRot = ArrowComponent->GetComponentRotation();
	
	FActorSpawnParameters ActorSpawnParameters;
	ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	AActor* ParentActor = GetParentActor();
	ActorSpawnParameters.Owner = ParentActor;

	World->SpawnActor<AArrowProjectile>(ArrowProjectile, SpawnLoc, SpawnRot, ActorSpawnParameters);
	GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Red, FString::Printf(TEXT("Bow Fired!")));
	
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

