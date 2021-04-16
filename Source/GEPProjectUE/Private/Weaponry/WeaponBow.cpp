// Fill out your copyright notice in the Description page of Project Settings.


#include "Weaponry/WeaponBow.h"

#include "Components/ArrowComponent.h"
#include "WeaponCombatTypeEnum.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
AWeaponBow::AWeaponBow()
{
	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow Spawn Location"));
	ArrowComponent->SetupAttachment(RootSceneComponent);

	EWeaponType = EWeapon_Combat_Type::Ranged;

	GravityIncrement = 0.0035f;
	GravitySpeedFactor = 6.0f;
	StartGravity = 0.2f;
	DrawTimeRequired = 0.15f;
	CurrentGravity = StartGravity;
}

bool AWeaponBow::FireHeld_Implementation()
{
	UWorld* const World = GetWorld();
	if (!World && ArrowProjectile == nullptr)
		return false;

	// Line Trace Arguments
	FHitResult Hit;
	FVector const SpawnLoc = ArrowComponent->GetComponentLocation();
	const FVector Forward = UGameplayStatics::GetPlayerController(World, 0)->PlayerCameraManager->GetActorForwardVector();
	const FVector Start = UGameplayStatics::GetPlayerController(World, 0)->PlayerCameraManager->GetCameraLocation();
	FVector End = Start + (Forward * 15000.0f);
	
	// Gravity
	FVector Distance = (Forward * 15000.0f) / GravitySpeedFactor;
	
	// Line trace from camera outwards
    bool TraceHit = World->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility);

	if (TraceHit)
    {
	    // Gravity Increment
    	Distance = Hit.ImpactPoint;
    }

	// Set increment
	float Length = Distance.Size();
	float Increment = 1 / Length;
	Increment *= GravitySpeedFactor;
	GravityIncrement = Increment;
	
	// Set current gravity
	CurrentGravity = CurrentGravity - GravityIncrement;
	CurrentGravity = FMath::Clamp(CurrentGravity, 0.0f, StartGravity);

	// Increase draw time
	CurrentDrawTime += Increment;
	
	// Predicted Path Arguments
	// Parameters
	FVector Offset = FVector(0.0f, 0.0f, CurrentGravity);
	FVector LaunchVelocity = (Forward - Offset) * 15000.0f;
	FPredictProjectilePathParams Params;
	Params.StartLocation = Start;
	Params.LaunchVelocity = LaunchVelocity;
	Params.ProjectileRadius = 2.0f;
	Params.MaxSimTime = 2.0f;
	Params.bTraceWithCollision = true;
	Params.bTraceComplex = true;
	Params.DrawDebugType = EDrawDebugTrace::None;
	Params.DrawDebugTime = 1.0f;
	Params.SimFrequency = 30.0f; // Recommended by Unreal staff for accuracy. Can take up performance
	Params.bTraceWithChannel = true;
	Params.OverrideGravityZ = CurrentGravity;
	Params.TraceChannel = ECC_Visibility;

	// Predicted Path
	bool HasHit = UGameplayStatics::PredictProjectilePath(World, Params, PredictResult);
	FVector EndLocation;
	EndLocation = HasHit ? PredictResult.HitResult.ImpactPoint : PredictResult.LastTraceDestination.Location;

	SpawnLocation = ArrowComponent->GetComponentLocation();
	SpawnRotation = UKismetMathLibrary::FindLookAtRotation(SpawnLocation, EndLocation);

	OnWeaponFireHeldEvent.Broadcast();
	return true;
}

// Fire first pressed
bool AWeaponBow::Fire_Implementation()
{
	// Reset Gravity for the bow
	CurrentGravity = StartGravity;
	// Reset draw time
	CurrentDrawTime = 0;

	OnWeaponFiredEvent.Broadcast();
	return true;
}

// Fire released
bool AWeaponBow::FireReleased_Implementation()
{
	UWorld* const World = GetWorld();

	if (!World && ArrowProjectile == nullptr)
		return false;

	// Stop if bow isn't 'drawn'
	if (DrawTimeRequired > CurrentDrawTime)
		return false;
		
	
	FActorSpawnParameters ActorSpawnParameters;
	ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	AActor* ParentActor = GetParentActor();
	ActorSpawnParameters.Owner = ParentActor;
	
	World->SpawnActor<AArrowProjectile>(ArrowProjectile, SpawnLocation, SpawnRotation, ActorSpawnParameters);

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

