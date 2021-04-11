// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Initializeable.h"
#include "Pickups/PickupItem.h"


#include "ArrowTree.generated.h"

UCLASS()
class GEPPROJECTUE_API AArrowTree : public AActor, public IInitializeable
{
	GENERATED_BODY()

	/* HEALTH */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UHealthComponent* Health;

	/* ARROW */
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<APickupItem>> ArrowsToDrop;

	/* MESH */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* MeshComponent;
	
	/* SPAWN POINT */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* ArrowSpawnRange;
	
public:	
	// Sets default values for this actor's properties
	AArrowTree();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int AmountToDrop;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Initialize_Implementation() override;
	UFUNCTION(BlueprintImplementableEvent)
    void ReceiveInitialized();

	UFUNCTION(BlueprintCallable)
    virtual void TreeDestroyed();

	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveTreeDestroyed();

	UFUNCTION(BlueprintCallable)
	void DropArrows();

public:	


};
