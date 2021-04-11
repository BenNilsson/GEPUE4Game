// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

// DELEGATE, Used to update UI
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GEPPROJECTUE_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	UFUNCTION(BlueprintCallable)
	bool AddItem(class UItem* Item, int amount = 1);
	UFUNCTION(BlueprintCallable)
	bool RemoveItem(class UItem* Item);
	UFUNCTION(BlueprintCallable)
    bool ContainsItem(class UItem* Item);
	UFUNCTION(BlueprintCallable)
    class UArrowItem* GetArrow();

	UPROPERTY(EditDefaultsOnly, Category="Inventory")
	int MaxSize;

	UPROPERTY(BlueprintAssignable, Category="Inventory")
	FOnInventoryUpdated OnInventoryUpdated;
	
	UPROPERTY(EditAnywhere, Instanced)
	TArray<class UItem*> DefaultItems;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Items")
	TArray<class UItem*> Items;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

};
