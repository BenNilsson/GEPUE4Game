// Fill out your copyright notice in the Description page of Project Settings.

#include "GameMode/GameModeDeerHunting.h"
#include "GameFramework/PlayerStart.h"
#include "Interfaces/GetPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PlayerControllerGEP.h"
#include "GameMode/ActorSpawner.h"

AGameModeDeerHunting::AGameModeDeerHunting() : Super()
{
	DefaultPawnClass = nullptr;
}

AActor* AGameModeDeerHunting::FindPlayerStart_Implementation(AController* Player, const FString& IncomingName)
{
	if (PlayerStarts.Num() == 0)
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), PlayerStarts);
	
	if (PlayerStarts.Num() > 0)
		return PlayerStarts[0];

	return nullptr;
}

void AGameModeDeerHunting::PostLogin(APlayerController* NewPlayer)
{
	PlayerControllers.AddUnique(NewPlayer);

	if (!NewPlayer->GetClass()->ImplementsInterface(UGetPlayerController::StaticClass()))
		return;

	APlayerControllerGEP* PlayerController = IGetPlayerController::Execute_GetPlayerControllerGEP(NewPlayer);
	
	if (!PlayerController->GetClass()->ImplementsInterface(UInitializeable::StaticClass()))
		return;

	// Initialize the player controller
	IInitializeable::Execute_Initialize(PlayerController);

	// Add the player to the spawner
	if (ActorSpawner)
	{
		ActorSpawner->PlayersToSpawnActorsNearby.AddUnique(PlayerController);
	}

	Super::PostLogin(NewPlayer);
}

void AGameModeDeerHunting::Logout(AController* Exiting)
{
	PlayerControllers.Remove(Exiting);

	if (!Exiting->GetClass()->ImplementsInterface(UGetPlayerController::StaticClass()))
		return;

	APlayerControllerGEP* PlayerController = IGetPlayerController::Execute_GetPlayerControllerGEP(Exiting);
	// Unbind events such as player death

	if (ActorSpawner)
	{
		ActorSpawner->PlayersToSpawnActorsNearby.RemoveSingle(PlayerController);
	}
	
	Super::Logout(Exiting);
}

void AGameModeDeerHunting::BeginPlay()
{
	CreateSpawner();
}

void AGameModeDeerHunting::OnActorKilled()
{
	
}

void AGameModeDeerHunting::CreateSpawner()
{
	if (!ActorSpawnerToSpawn)
		return;
	
	UWorld* const World = GetWorld();
	if (!World)
		return;

	const FVector SpawnLoc = FVector::ZeroVector;
	const FRotator SpawnRot = FRotator::ZeroRotator;
	
	FActorSpawnParameters ActorSpawnParameters;
	ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	AActor* Spawner = World->SpawnActor<AActor>(ActorSpawnerToSpawn, SpawnLoc, SpawnRot, ActorSpawnParameters);
	
	if (Spawner->GetClass()->ImplementsInterface(UInitializeable::StaticClass()))
	{
		ActorSpawner = Cast<AActorSpawner>(Spawner);

		// Add all currently existing players to the spawner
		for (int i = 0; i < PlayerControllers.Num(); i++)
		{
			if (!PlayerControllers[i]->GetClass()->ImplementsInterface(UGetPlayerController::StaticClass()))
				continue;

			ActorSpawner->PlayersToSpawnActorsNearby.AddUnique(IGetPlayerController::Execute_GetPlayerControllerGEP(PlayerControllers[i]));
		}

		// Bind Death event
		ActorSpawner->OnActorDeath.AddDynamic(this, &AGameModeDeerHunting::OnActorKilled);

		// Initialize spawner (enable it)
		IInitializeable::Execute_Initialize(Spawner);
	}
}
