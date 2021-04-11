// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldObjects/CrateSpawner.h"

#include "NavigationSystem.h"
#include "WorldObjects/ArrowCrate.h"


// Sets default values
ACrateSpawner::ACrateSpawner()
{
	PrimaryActorTick.bCanEverTick = false;

	MaxCratesInWorld = 30;
	MinSpawnRadius = 10.0f;
	MaxSpawnRadius = 25.0f;
	RespawnTime = 10.0f;
}

// Called when the game starts or when spawned
void ACrateSpawner::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < MaxCratesInWorld; i++)
	{
		SpawnCrateInWorld();
	}
}

void ACrateSpawner::SpawnCrateInWorld()
{
	UWorld* const World = GetWorld();

	if (!CrateToSpawn)
		return;

	if (!World)
		return;

	const FVector Origin = GetActorLocation();
	const FRotator SpawnRotation = GetActorRotation();
	FVector SpawnLocation = FVector::ZeroVector;

	/// --------- Get navmesh
	UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(World);
	if (!NavSys)
	{
		// No navmesh found
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Navmesh Not Found"));
		return;
	}

	/// --------- Get random point on navmesh in annulus
	// Get random point between min and max radius
	const auto RandPointInCircle = FMath::RandPointInCircle(1);
	FVector RandomDirection = FVector(RandPointInCircle.X, RandPointInCircle.Y, 0);
	RandomDirection.Normalize();
	
	const float Distance = FMath::RandRange(MinSpawnRadius, MaxSpawnRadius);

	auto RandomPoint = Origin + RandomDirection * Distance;
	RandomPoint.Z = Origin.Z;
	
	// Get random point on NavMesh
	FNavLocation Result;

	const bool Success = NavSys->GetRandomReachablePointInRadius(RandomPoint, 1000, Result);
	if (!Success)
	{
		// Did not find a location
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Navmesh Location Not Found"));
	}

	//const FVector RandomPointInAnnulus = FVector(Result.Location.X * Range, Result.Location.Y * Range, Result.Location.Z);
	
	// Location Found
	SpawnLocation = Result.Location;
	

	/// ------------ Spawn Crate
	FActorSpawnParameters ActorSpawnParameters;
	ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	AActor* SpawnedPawn = World->SpawnActor<AActor>(CrateToSpawn, SpawnLocation, SpawnRotation, ActorSpawnParameters);
	
	if (SpawnedPawn->GetClass()->ImplementsInterface(UGetCrate::StaticClass()))
	{
		AArrowCrate* Crate = IGetCrate::Execute_GetCrate(SpawnedPawn);

		Crate->OnCrateDestroyed.AddDynamic(this, &ACrateSpawner::CrateDestroyed);
		ReceiveCrateDestroyed(Crate); // Call BP Function
	}
	
}	

void ACrateSpawner::CrateDestroyed(AArrowCrate* DestroyedCrate)
{
	ReceiveCrateDestroyed(DestroyedCrate); // Call BP Function
	FTimerHandle RespawnTimer;
	GetWorldTimerManager().SetTimer(RespawnTimer, this, &ACrateSpawner::SpawnCrateInWorld, RespawnTime, false);
}

