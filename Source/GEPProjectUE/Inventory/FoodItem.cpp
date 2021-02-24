// Fill out your copyright notice in the Description page of Project Settings.


#include "FoodItem.h"
#include "GEPProjectUE/PlayerControllerCPP.h"

void UFoodItem::Use(APlayerControllerCPP* Character)
{
	if (Character)
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Food Item Function Not Implemented"));
}
