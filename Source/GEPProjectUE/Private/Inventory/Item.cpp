// Fill out your copyright notice in the Description page of Project Settings.


#include "GEPProjectUE/Public/Inventory/Item.h"

UItem::UItem()
{
	ItemDisplayName = FText::FromString("Item");
	ItemDescription = FText::FromString("This item has no description...");
}

void UItem::Use(APlayerControllerCPP* Character)
{
}
