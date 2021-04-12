// Fill out your copyright notice in the Description page of Project Settings.

#include "Pickups/PickupBase.h"

// Sets default values
APickupBase::APickupBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Scene Component
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = SceneComponent;

	// Create Mesh
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	
	// Create overlap sphere
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereComponent->SetupAttachment(Mesh);

	InitialLifeSpan = 20;
}

void APickupBase::NotifyActorBeginOverlap(AActor* OtherActor)
{
	OnActivate(OtherActor);
}

void APickupBase::OnActivate_Implementation(AActor* PickedUpBy)
{
	
}

// Called when the game starts or when spawned
void APickupBase::BeginPlay()
{
	Super::BeginPlay();
}