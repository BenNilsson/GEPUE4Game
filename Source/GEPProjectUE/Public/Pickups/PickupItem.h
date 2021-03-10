// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/PickupBase.h"
#include "PickupItem.generated.h"

/**
 * 
 */
UCLASS()
class GEPPROJECTUE_API APickupItem : public APickupBase
{
	GENERATED_BODY()

	/* ITEM TO PICK UP */
	UPROPERTY(EditAnywhere, Instanced, Category="Pickup")
	class UItem* Item;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:

	virtual void OnActivate_Implementation(AActor* PickedUpBy) override;
};
