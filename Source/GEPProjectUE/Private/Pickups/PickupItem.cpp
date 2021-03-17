// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/PickupItem.h"
#include "Interfaces/GetPlayerController.h"
#include "Inventory/InventoryComponent.h"
#include "Inventory/Item.h"
#include "Player/PlayerControllerCPP.h"

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
	if (PickedUpBy->GetClass()->ImplementsInterface(UGetPlayerController::StaticClass()))
	{
		APlayerControllerCPP* PlayerControllerCPP = IGetPlayerController::Execute_GetPlayerController(PickedUpBy);

		if (!PlayerControllerCPP)
			return;

		// Check for inventory interface
		if (PlayerControllerCPP->GetClass()->ImplementsInterface(UGetInventory::StaticClass()))
		{
			UInventoryComponent* Inventory = IGetInventory::Execute_GetInventory(PlayerControllerCPP);

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
