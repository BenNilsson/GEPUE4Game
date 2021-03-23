// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inventory/Item.h"
#include "ArrowItem.generated.h"

/**
 * 
 */
UCLASS()
class GEPPROJECTUE_API UArrowItem : public UItem
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class AArrowProjectile> ArrowProjectile;
};
