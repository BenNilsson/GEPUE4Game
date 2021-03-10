// Fill out your copyright notice in the Description page of Project Settings.

#include "GEPProjectUE/Public/AI/AIBase.h"
#include "GEPProjectUE/Public/Components/HealthComponent.h"

// Sets default values
AAIBase::AAIBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Mesh Component
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
	
	// Health Component
	Health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
	
	
}

// Called when the game starts or when spawned
void AAIBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAIBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAIBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

