// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Initializeable.h"
#include "Interfaces/Interactable.h"

#include "StartGameButton.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnButtonPressed, bool, Start);

UCLASS()
class GEPPROJECTUE_API AStartGameButton : public AActor, public IInteractable, public IInitializeable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStartGameButton();

	FOnButtonPressed OnButtonPressed;

	virtual void Initialize_Implementation() override;

protected:

	bool bIsActive;

public:	
	virtual bool Interact_Implementation() override;
	
};
