// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/DeerAI.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ADeerAI::ADeerAI()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

}

// Called when the game starts or when spawned
void ADeerAI::BeginPlay()
{
	Super::BeginPlay();
}

void ADeerAI::AIDied()
{
	SetCanBeDamaged(false);
	ReceiveAIDied();
	OnDeath.Broadcast(this);
}
