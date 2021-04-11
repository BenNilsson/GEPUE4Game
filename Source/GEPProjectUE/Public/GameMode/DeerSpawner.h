// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Initializeable.h"

#include "DeerSpawner.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActorDeath, AActor*, ActorDied);

UCLASS()
class GEPPROJECTUE_API ADeerSpawner : public AActor, public IInitializeable
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> ActorToSpawn;

	UPROPERTY(EditDefaultsOnly)
	float RespawnTime;
	UPROPERTY(EditDefaultsOnly)
	float SpawnRadiusMin;
	UPROPERTY(EditDefaultsOnly)
	float SpawnRadiusMax;
	UPROPERTY(EditDefaultsOnly)
	int ActorsToSpawnAtStart;
	UPROPERTY(EditDefaultsOnly)
	int MaxActorsSpawned;
	UPROPERTY(VisibleDefaultsOnly)
	int CurrentActorsInLevel;
	
	FTimerHandle RespawnTimer;

	UPROPERTY(EditDefaultsOnly)
	TArray<AActor*> ActorsSpawned;
	
public:	
	// Sets default values for this actor's properties
	ADeerSpawner();

	FOnActorDeath OnActorDeath;

	UPROPERTY()
	TArray<class APlayerController*> PlayersToSpawnActorsNearby;
	
	UFUNCTION(BlueprintCallable)
	void SpawnActorInWorld();

	UFUNCTION(BlueprintCallable)
    void ActorDied(AActor* ActorDied);

	UFUNCTION()
	void EnableSpawner();

	UFUNCTION()
    void DisableSpawner();

	virtual void Initialize_Implementation() override;
	UFUNCTION(BlueprintImplementableEvent)
    void ReceiveInitialized();
};
