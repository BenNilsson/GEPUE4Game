// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/AIBase.h"
#include "Components/HealthComponent.h"

// Sets default values
AAIBase::AAIBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	// Health Component
	Health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));

	// Set Speeds
	WalkingSpeed = 200.0f;
	RunningSpeed = 800.0f;
}

// Called when the game starts or when spawned
void AAIBase::BeginPlay()
{
	Super::BeginPlay();

	if (Health->GetClass()->ImplementsInterface(UInitializeable::StaticClass()))
	{
		IInitializeable::Execute_Initialize(Health);
		Health->OnHealthBelowZero.AddDynamic(this, &AAIBase::AIDied);
	}
	
	
}

void AAIBase::AIDied()
{
	OnDeath.Broadcast(this);
}

// Called to bind functionality to input
void AAIBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}