// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/FoodItem.h"
#include "Player/PlayerCharacter.h"

void UFoodItem::Use(APlayerCharacter* Character)
{
	if (Character)
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Food Item Function Not Implemented"));
}
