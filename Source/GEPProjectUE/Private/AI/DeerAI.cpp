// Fill out your copyright notice in the Description page of Project Settings.


#include "GEPProjectUE/Public/AI/DeerAI.h"

// Sets default values
ADeerAI::ADeerAI()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADeerAI::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADeerAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
