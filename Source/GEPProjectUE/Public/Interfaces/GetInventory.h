// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GetInventory.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UGetInventory : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GEPPROJECTUE_API IGetInventory
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    class UInventoryComponent* GetInventory();
};