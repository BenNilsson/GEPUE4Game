// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "InventoryComponent.h"
#include "UObject/NoExportTypes.h"
#include "Item.generated.h"

class UStaticMesh;
class UTexture2D;

UCLASS(Abstract, BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced)
class GEPPROJECTUE_API UItem : public UObject
{
	GENERATED_BODY()

public:
	UItem();

	/* Item ID */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Item")
	int ItemID;
	
	/* Item Mesh */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Item")
	UStaticMesh* ItemMesh;

	/* Item Icon */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Item")
	UTexture2D* ItemIcon;

	/* Item Name */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Item")
	FText ItemDisplayName;

	/* Item Description */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Item", meta = (MultiLine = true))
	FText ItemDescription;

	/* Max Size */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	int ItemMaxStackSize;

	/* Current Size */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	int ItemCurrentStackSize;
	
	/* Owner of the Item */
	UPROPERTY()
	UInventoryComponent* Inventory;

	/* PUBLIC FUNCTIONS */
	virtual void Use(class APlayerCharacter* Character);
	
	// Allows for implementation of function within BluePrints
	UFUNCTION(BlueprintImplementableEvent)
	void UseBP(class APlayerCharacter* Character); 
};
