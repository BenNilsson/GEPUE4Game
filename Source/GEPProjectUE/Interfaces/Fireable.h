// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Fireable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UFireable : public UInterface
{
	GENERATED_BODY()
};

class GEPPROJECTUE_API IFireable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool Fire();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    bool FireReleased();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    bool FireHeld();
};
