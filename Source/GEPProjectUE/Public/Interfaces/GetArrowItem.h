// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GetArrowItem.generated.h"

UINTERFACE(MinimalAPI)
class UGetArrowItem : public UInterface
{
	GENERATED_BODY()
};

class GEPPROJECTUE_API IGetArrowItem
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    class UArrowItem* GetArrowItem();
};
