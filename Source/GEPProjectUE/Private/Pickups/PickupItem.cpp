// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/PickupItem.h"
#include "Interfaces/GetPlayerCharacter.h"
#include "Inventory/InventoryComponent.h"
#include "Inventory/Item.h"
#include "Player/PlayerCharacter.h"

void APickupItem::BeginPlay()
{
	Super::BeginPlay();
	
	if (!Item)
		return;
	
	Mesh->SetStaticMesh(Item->ItemMesh);
	Mesh->SetSimulatePhysics(true);
}

void APickupItem::OnActivate_Implementation(AActor* PickedUpBy)
{
	if (Item == nullptr)
		return;

	// Check if whoever activated this is a player
	if (PickedUpBy->GetClass()->ImplementsInterface(UGetPlayerCharacter::StaticClass()))
	{
		APlayerCharacter* PlayerCharacter = IGetPlayerCharacter::Execute_GetPlayerCharacter(PickedUpBy);

		if (!PlayerCharacter)
			return;

		// Check for inventory interface
		if (PlayerCharacter->GetClass()->ImplementsInterface(UGetInventory::StaticClass()))
		{
			UInventoryComponent* Inventory = IGetInventory::Execute_GetInventory(PlayerCharacter);

			if (!Inventory)
				return;

			// Add inventory
			if (Inventory->AddItem(Item))
			{
				// Destroy this actor
				this->Destroy(false, false);
			}
		}
	}
}
