// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/InventoryComponent.h"
#include "Inventory/Item.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	MaxSize = 20;
}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	for (auto& Item : DefaultItems)
	{
		AddItem((Item));
	}
}

bool UInventoryComponent::AddItem(UItem* Item, int amount)
{
	if (Items.Num() >= MaxSize || !Item)
		return false;

	// Iterate through the items and check if an item with the same type is currently in the inventory
	for(int i = 0; i < MaxSize; i++)
	{
		if (i >= Items.Num() || !Item)
			continue;
		
		if (Items[i]->ItemID != Item->ItemID)
			continue;
		
		// ITEM FOUND
		// If stack size is less than max stack size, increment
		if (Items[i]->ItemCurrentStackSize < Items[i]->ItemMaxStackSize)
		{
			Items[i]->ItemCurrentStackSize++;
			OnInventoryUpdated.Broadcast();
			return true;
		}
	}

	// Considering no items of same type was found or item stack size was full, add a new item.
	Items.Add(Item);
	Item->ItemCurrentStackSize = 1;
	Item->Inventory = this;
	OnInventoryUpdated.Broadcast();
	
	return true;
}

bool UInventoryComponent::RemoveItem(UItem* Item)
{
	if (!Item)
		return false;

	// Iterate through the items and check if an item with the same type is currently in the inventory
	for(int i = MaxSize - 1; i >= 0; i--)
	{
		if (Items.Num() < i)
			continue;
		
		if (Items[i]->ItemID != Item->ItemID)
			continue;
	
		// If stack size is greater than max stack size, remove one
		if (Items[i]->ItemCurrentStackSize > Items[i]->ItemMaxStackSize)
		{
			Items[i]->ItemCurrentStackSize--;
			// Check if 0, if so delete
			if (Items[i]->ItemCurrentStackSize <= 0)
			{
				Item->Inventory = nullptr;
				Items.RemoveSingle((Item));
			}
			OnInventoryUpdated.Broadcast();
			return true;
		}
	}

	Item->Inventory = nullptr;
	Items.RemoveSingle((Item));
	OnInventoryUpdated.Broadcast();

	return true;
}
