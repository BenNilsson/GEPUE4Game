// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldObjects/ArrowCrate.h"


#include "Components/BoxComponent.h"
#include "Components/HealthComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AArrowCrate::AArrowCrate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Health Component
	Health = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

	// Mesh 
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TreeMesh"));
	RootComponent = MeshComponent;

	// Arrow Spawn Position
	ArrowSpawnRange = CreateDefaultSubobject<UBoxComponent>(TEXT("ArrowSpawnRange"));

	// Amount of arrows to drop
	AmountToDrop = 10;
}

// Called when the game starts or when spawned
void AArrowCrate::BeginPlay()
{
	Super::BeginPlay();
	
	Initialize_Implementation();
}

void AArrowCrate::Initialize_Implementation()
{
	if (Health->GetClass()->ImplementsInterface(UInitializeable::StaticClass()))
	{
		IInitializeable::Execute_Initialize(Health);
		ReceiveInitialized();
		Health->OnHealthBelowZero.AddDynamic(this, &AArrowCrate::CrateDestroyed);
	}
}

void AArrowCrate::CrateDestroyed()
{
	DropArrows();
	ReceiveCrateDestroyed(); // BP Event
	OnCrateDestroyed.Broadcast(this);
	Destroy(false, false);
}

void AArrowCrate::DropArrows()
{
	UWorld* const World = GetWorld();
	
	for (int i = 0; i < AmountToDrop; i++)
	{
		auto RandomArrowToDrop = ArrowsToDrop[FMath::RandRange(0, ArrowsToDrop.Num() - 1)];
		
		FActorSpawnParameters ActorSpawnParameters;
		ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		const FVector Origin = ArrowSpawnRange->GetComponentLocation();
		const FVector Extents = ArrowSpawnRange->GetScaledBoxExtent();

		FVector SpawnPosition = GetActorLocation() + UKismetMathLibrary::RandomPointInBoundingBox(Origin, Extents);
		
		World->SpawnActor<AActor>(RandomArrowToDrop, SpawnPosition, FRotator::ZeroRotator, ActorSpawnParameters);
	}
	
}

AArrowCrate* AArrowCrate::GetCrate_Implementation()
{
	return this;
}

