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
}

bool AStartGameButton::Interact_Implementation()
{
	bIsActive = !bIsActive;
	
	OnButtonPressed.Broadcast(bIsActive);
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Magenta, FString::Printf(TEXT("Start Game Button Clicked")));
	return true;
}


