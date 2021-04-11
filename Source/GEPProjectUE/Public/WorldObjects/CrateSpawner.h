// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/GetCrate.h"

#include "CrateSpawner.generated.h"

UCLASS()
class GEPPROJECTUE_API ACrateSpawner : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> CrateToSpawn;

	UPROPERTY(EditDefaultsOnly)
	int MaxCratesInWorld;
	
	UPROPERTY(EditDefaultsOnly)
	float MinSpawnRadius;

	UPROPERTY(EditDefaultsOnly)
	float MaxSpawnRadius;

	UPROPERTY(EditDefaultsOnly)
	float RespawnTime;
	
public:	
	// Sets default values for this actor's properties
	ACrateSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UFUNCTION(BlueprintCallable)
    void SpawnCrateInWorld();
	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveCrateSpawnedInWorld(AArrowCrate* Crate); // BP

	UFUNCTION(BlueprintCallable)
    void CrateDestroyed(AArrowCrate* DestroyedCrate);
	UFUNCTION(BlueprintImplementableEvent)
    void ReceiveCrateDestroyed(AArrowCrate* Crate); // BP

	
};
