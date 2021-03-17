// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/Item.h"

UItem::UItem()
{
	ItemDisplayName = FText::FromString("Item");
	ItemDescription = FText::FromString("This item has no description...");
	ItemCurrentStackSize = 0;
	ItemMaxStackSize = 50;
}

void UItem::Use(APlayerControllerCPP* Character)
{
}
