// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/ArrowItem.h"

#include "Player/PlayerControllerCPP.h"

void UArrowItem::Use(APlayerControllerCPP* Character)
{
	if (!Character)
		return;

	// Select Arrow On Player
	Character->ArrowItem = this;
}

UArrowItem* UArrowItem::GetArrowItem_Implementation()
{
	return this;
}
