// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/InventoryComponent.h"
#include "Inventory/ArrowItem.h"
#include "Inventory/Item.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	MaxSize = 20;
}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{

	for (auto& Item : DefaultItems)
	{
		const auto StackSize = Item->ItemCurrentStackSize;
		for (int i = 0; i < StackSize; ++i)
		{
			AddItem(Item);
		}
	}
	
	Super::BeginPlay();
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
		if (Items.Num() <= i)
			continue;
		
		if (Items[i]->ItemID != Item->ItemID)
			continue;
	
		// If stack size is greater than max stack size, remove one
		if (Items[i]->ItemCurrentStackSize > 0)
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

bool UInventoryComponent::ContainsItem(UItem* Item)
{
	bool HasItem = false;
	if (!Item || Items.Num() < 0)
		return false;

	
	HasItem = (Items.FindByPredicate([&](UItem* InItem)
	{
		if (InItem->ItemID == Item->ItemID)
			return true;
		
		return false;
	}) != nullptr);

	return HasItem;
}

UArrowItem* UInventoryComponent::GetArrow()
{
	if (Items.Num() < 0)
		return nullptr;

	for (int i = 0; i < Items.Num(); i++)
	{
		if (Items[i]->IsA(UArrowItem::StaticClass()))
		{
			// Get Bow & Change Arrow Type
			if (!Items[i]->GetClass()->ImplementsInterface(UGetArrowItem::StaticClass()))
				continue;
					
			UArrowItem* ArrowItem = IGetArrowItem::Execute_GetArrowItem(Items[i]);
			if (ArrowItem)
				return ArrowItem;
		}
	}

	return nullptr;
}
