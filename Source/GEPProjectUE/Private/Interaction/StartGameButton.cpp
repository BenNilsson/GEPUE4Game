// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/StartGameButton.h"

// Sets default values
AStartGameButton::AStartGameButton()
{
	PrimaryActorTick.bCanEverTick = false;
	bIsActive = false;
}

void AStartGameButton::Initialize_Implementation()
{
	bIsActive = false;
	ReceiveInitialized();
}

void AStartGameButton::BeginPlay()
{
	bIsActive = false;
}  

bool AStartGameButton::Interact_Implementation()
{
	bIsActive = !bIsActive;
	
	OnButtonPressed.Broadcast(bIsActive);

	/*
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, FString::Printf(TEXT("[Start Button] Active: %s"), bIsActive ? TEXT("true") : TEXT("false")));
	*/
	return true;
}


