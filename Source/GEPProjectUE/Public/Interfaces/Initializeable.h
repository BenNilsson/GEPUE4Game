// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Initializeable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInitializeable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GEPPROJECTUE_API IInitializeable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void Initialize();
};
