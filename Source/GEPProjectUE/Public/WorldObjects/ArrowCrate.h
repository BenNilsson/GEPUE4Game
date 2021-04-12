// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/GetCrate.h"
#include "Interfaces/Initializeable.h"
#include "Pickups/PickupItem.h"


#include "ArrowCrate.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCrateDestroyed, AArrowCrate*, DestroyedCrate);

UCLASS()
class GEPPROJECTUE_API AArrowCrate : public AActor, public IInitializeable, public IGetCrate
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
	AArrowCrate();

	FOnCrateDestroyed OnCrateDestroyed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int AmountToDrop;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Initialize_Implementation() override;
	UFUNCTION(BlueprintImplementableEvent)
    void ReceiveInitialized();

	UFUNCTION(BlueprintCallable)
    virtual void CrateDestroyed();

	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveCrateDestroyed();

	UFUNCTION(BlueprintCallable)
	void DropArrows();

public:	
	virtual AArrowCrate* GetCrate_Implementation() override;

};
