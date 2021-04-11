// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UHealthComponent::Initialize_Implementation()
{
	// Bind Actor to this component
	AActor* Owner = GetOwner();
	if (Owner)
		Owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
	
	Health = HealthStart; // Set Health to its Start health.
	
	ReceiveInitialized();
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* InstigatedBy, AActor* DamageCauser)
{
	if (DamagedActor == nullptr)
		return;
	
	if (Damage <= 0) return;

	Health -= Damage; // Decrease health
	Health = FMath::Clamp(Health, .0f, HealthStart); // Clamp to avoid going below 0

	if (Health <= 0)
		OnHealthBelowZero.Broadcast();
	
}

