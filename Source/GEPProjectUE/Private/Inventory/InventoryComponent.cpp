// Fill out your copyright notice in the Description page of Project Settings.


#include "GEPProjectUE/Public/Inventory/InventoryComponent.h"
#include "GEPProjectUE/Public/Inventory/Item.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	MaxSize = 30;
}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	for (auto& Item : Items)
	{
		AddItem((Item));
	}
}

bool UInventoryComponent::AddItem(UItem* Item)
{
	if (Items.Num() >= MaxSize || !Item)
		return false;
	
	Items.Add(Item);
	Item->Inventory = this;
	OnInventoryUpdated.Broadcast();
	
	return true;
}

bool UInventoryComponent::RemoveItem(UItem* Item)
{
	if (!Item)
		return false;

	Item->Inventory = nullptr;
	Items.RemoveSingle((Item));
	OnInventoryUpdated.Broadcast();

	return true;
}
