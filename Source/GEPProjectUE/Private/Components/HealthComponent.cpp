// Fill out your copyright notice in the Description page of Project Settings.

#include "GEPProjectUE/Public/Components/HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// Bind Actor to this component
	AActor* Owner = GetOwner();
	if (Owner)
		Owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
	
	Health = HealthStart; // Set Health to its Start health.
	
}

void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0) return;

	Health -= Damage; // Decrease health
	Health = FMath::Clamp(Health, .0f, HealthStart); // Clamp to avoid going below 0
}

