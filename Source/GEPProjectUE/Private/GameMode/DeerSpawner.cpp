// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/DeerSpawner.h"

#include "AI/AIBase.h"
#include "Interfaces/GetBaseAI.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"

// Sets default values
ADeerSpawner::ADeerSpawner()
{
	PrimaryActorTick.bCanEverTick = false;

	RespawnTime = 10.0f;
	ActorsToSpawnAtStart = 5;
	SpawnRadiusMin = 500.0f;
	SpawnRadiusMax = 1000.0f;
	MaxActorsSpawned = 20;
	CurrentActorsInLevel = 0;
}

void ADeerSpawner::SpawnActorInWorld()
{
	if (ActorToSpawn == nullptr)
		return;

	if (CurrentActorsInLevel >= MaxActorsSpawned)
		return;
	
	UWorld* const World = GetWorld();
	if (!World)
		return;
	
	FVector SpawnLoc = GetActorLocation();
	const FRotator SpawnRot = GetActorRotation();

#pragma region - NAVMESH POINT
	// Get point on navmesh
	// Origin - Random player's location
	FVector PlayerLocation = FVector::ZeroVector;

	const int PlayerIndex = FMath::RandRange(0.0f, static_cast<float>(PlayersToSpawnActorsNearby.Num()));
	const int PlayerCount = PlayersToSpawnActorsNearby.Num();
	if (PlayerCount > PlayerIndex)
	{
		APlayerController* PlayerController = PlayersToSpawnActorsNearby[PlayerIndex];
		if (!PlayerController)
			return;

		PlayerLocation = PlayerController->GetPawn()->GetActorLocation();

		if (PlayerLocation == FVector::ZeroVector)
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("oof"));
	}

	UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(World);
	if (!NavSys)
	{
		// No navmesh found
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Navmesh Not Found"));
		return;
	}
	
	FNavLocation Result;

	const bool Success = NavSys->GetRandomReachablePointInRadius(PlayerLocation, SpawnRadiusMax, Result);
	if (!Success)
	{
		// Did not find a location
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Navmesh Location Not Found"));
		return;
	}

	// Location Found
	SpawnLoc = Result.Location;
	
#pragma endregion 
	
  	FActorSpawnParameters ActorSpawnParameters;
	ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	APawn* SpawnedPawn = World->SpawnActor<APawn>(ActorToSpawn, SpawnLoc, SpawnRot, ActorSpawnParameters);
	CurrentActorsInLevel++;
	ActorsSpawned.Add(SpawnedPawn);
	
	if (SpawnedPawn->GetClass()->ImplementsInterface(UGetBaseAI::StaticClass()))
	{
		AAIBase* AIBase = IGetBaseAI::Execute_GetAIBase(SpawnedPawn);

		if (!AIBase)
			return;

		AIBase->OnDeath.AddDynamic(this, &ADeerSpawner::ActorDied);
	}
}

void ADeerSpawner::ActorDied(AActor* ActorDied)
{
	// Spawn new enemy, broadcast death
	CurrentActorsInLevel--;
	ActorsSpawned.Remove(ActorDied);
	OnActorDeath.Broadcast(ActorDied);
}

void ADeerSpawner::EnableSpawner()
{
	for (int i = 0; i < ActorsToSpawnAtStart; i++)
	{
		SpawnActorInWorld();
	}

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "[Spawner] Enabled");
	
	GetWorldTimerManager().SetTimer(RespawnTimer, this, &ADeerSpawner::SpawnActorInWorld, RespawnTime, true);
}

void ADeerSpawner::DisableSpawner()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "[Spawner] Disabled");

	// Stop deer from spawning
	GetWorldTimerManager().ClearTimer(RespawnTimer);
	
	// Kill all deer
	for (int i = ActorsSpawned.Num() - 1; i >= 0; i--)
	{
		ActorsSpawned[i]->Destroy(false, true);
	}
	ActorsSpawned.Empty();
	
}

void ADeerSpawner::Initialize_Implementation()
{
	CurrentActorsInLevel = 0;
	ReceiveInitialized();
}
