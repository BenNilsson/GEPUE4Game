// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerControllerGEP.h"



#include "GameFramework/GameModeBase.h"
#include "Interfaces/Interactable.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PlayerCharacter.h"

APlayerControllerGEP::APlayerControllerGEP()
{
	
}

APlayerControllerGEP* APlayerControllerGEP::GetPlayerControllerGEP_Implementation()
{
	return this;
}

void APlayerControllerGEP::Initialize_Implementation()
{
	if (GetPawn() != nullptr)
		GetPawn()->Destroy();

	UWorld* const World = GetWorld();
	if (!World && !PawnToPossess)
		return;

	AActor* Start = UGameplayStatics::GetGameMode(World)->FindPlayerStart(this);
	FVector SpawnLoc = Start != nullptr ? Start->GetActorLocation() : FVector::ZeroVector;
	FRotator SpawnRot = Start != nullptr ? Start->GetActorRotation() : FRotator::ZeroRotator;

	FActorSpawnParameters ActorSpawnParameters;
	ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	APawn* SpawnedPawn = World->SpawnActor<APawn>(PawnToPossess, SpawnLoc, SpawnRot, ActorSpawnParameters);

	if (SpawnedPawn->GetClass()->ImplementsInterface(UInitializeable::StaticClass()))
		IInitializeable::Execute_Initialize(SpawnedPawn);

	GetWorldTimerManager().SetTimer(InteractionTimer, this, &APlayerControllerGEP::CheckForInteraction, 0.1f, true);
	
	Possess(SpawnedPawn);
}

void APlayerControllerGEP::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	// Bind Mapping Axis' to functions defined
	InputComponent->BindAxis("MoveForward", this, &APlayerControllerGEP::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &APlayerControllerGEP::MoveRight);
	
	// -- Mouse
	InputComponent->BindAxis("LookUp", this, &APlayerControllerGEP::LookUp);
	InputComponent->BindAxis("Turn", this, &APlayerControllerGEP::Turn);
	
	// -- Controller
	InputComponent->BindAxis("LookUpRate", this, &APlayerControllerGEP::LookUpAtRate); 
	InputComponent->BindAxis("TurnRate", this, &APlayerControllerGEP::TurnAtRate);

	// Bind Mapping Actions
	InputComponent->BindAction("Jump", IE_Pressed, this, &APlayerControllerGEP::Jump);
	InputComponent->BindAction("Sprint", IE_Pressed, this, &APlayerControllerGEP::Sprint);
	InputComponent->BindAction("Sprint", IE_Released, this, &APlayerControllerGEP::Sprint);
	InputComponent->BindAction("Crouch", IE_Pressed, this, &APlayerControllerGEP::CrouchTriggered);

	// Weapon Fire Actions
	InputComponent->BindAction("Fire", IE_Pressed, this, &APlayerControllerGEP::WeaponFireTriggered);
	InputComponent->BindAction("Fire", IE_Released, this, &APlayerControllerGEP::WeaponFireReleased);

	// Interact
	InputComponent->BindAction("Interact", IE_Pressed, this, &APlayerControllerGEP::Interact);
}

void APlayerControllerGEP::MoveForward(float Value)
{
	if (!GetPawn()->GetClass()->ImplementsInterface(UGetPlayerCharacter::StaticClass()))
		return;
					
	APlayerCharacter* PlayerCharacter = IGetPlayerCharacter::Execute_GetPlayerCharacter(GetPawn());
	if (PlayerCharacter != nullptr)
		PlayerCharacter->MoveForward(Value);
}

void APlayerControllerGEP::MoveRight(float Value)
{
	if (!GetPawn()->GetClass()->ImplementsInterface(UGetPlayerCharacter::StaticClass()))
		return;
					
	APlayerCharacter* PlayerCharacter = IGetPlayerCharacter::Execute_GetPlayerCharacter(GetPawn());
	if (PlayerCharacter != nullptr)
		PlayerCharacter->MoveRight(Value);
}

void APlayerControllerGEP::LookUp(float Value)
{
	if (!GetPawn()->GetClass()->ImplementsInterface(UGetPlayerCharacter::StaticClass()))
		return;
					
	APlayerCharacter* PlayerCharacter = IGetPlayerCharacter::Execute_GetPlayerCharacter(GetPawn());
	if (PlayerCharacter != nullptr)
		PlayerCharacter->AddControllerPitchInput(Value);
}

void APlayerControllerGEP::Turn(float Value)
{
	if (!GetPawn()->GetClass()->ImplementsInterface(UGetPlayerCharacter::StaticClass()))
		return;
					
	APlayerCharacter* PlayerCharacter = IGetPlayerCharacter::Execute_GetPlayerCharacter(GetPawn());
	if (PlayerCharacter != nullptr)
		PlayerCharacter->AddControllerYawInput(Value);
}

void APlayerControllerGEP::TurnAtRate(float Rate)
{
	if (!GetPawn()->GetClass()->ImplementsInterface(UGetPlayerCharacter::StaticClass()))
		return;
					
	APlayerCharacter* PlayerCharacter = IGetPlayerCharacter::Execute_GetPlayerCharacter(GetPawn());
	if (PlayerCharacter != nullptr)
		PlayerCharacter->TurnAtRate(Rate);
}

void APlayerControllerGEP::LookUpAtRate(float Rate)
{
	if (!GetPawn()->GetClass()->ImplementsInterface(UGetPlayerCharacter::StaticClass()))
		return;
					
	APlayerCharacter* PlayerCharacter = IGetPlayerCharacter::Execute_GetPlayerCharacter(GetPawn());
	if (PlayerCharacter != nullptr)
		PlayerCharacter->LookUpAtRate(Rate);
}

void APlayerControllerGEP::WeaponFireTriggered()
{
	if (!GetPawn()->GetClass()->ImplementsInterface(UGetPlayerCharacter::StaticClass()))
		return;
					
	APlayerCharacter* PlayerCharacter = IGetPlayerCharacter::Execute_GetPlayerCharacter(GetPawn());
	if (PlayerCharacter != nullptr)
		PlayerCharacter->WeaponFireTriggered();

	GetWorldTimerManager().SetTimer(WeaponFireHeldTimer, this, &APlayerControllerGEP::WeaponFireHeld, 0.01f, true);
}

void APlayerControllerGEP::WeaponFireHeld()
{
	if (!GetPawn()->GetClass()->ImplementsInterface(UGetPlayerCharacter::StaticClass()))
		return;
					
	APlayerCharacter* PlayerCharacter = IGetPlayerCharacter::Execute_GetPlayerCharacter(GetPawn());
	if (PlayerCharacter != nullptr)
		PlayerCharacter->WeaponFireHeld();
}

void APlayerControllerGEP::WeaponFireReleased()
{
	if (!GetPawn()->GetClass()->ImplementsInterface(UGetPlayerCharacter::StaticClass()))
		return;
					
	APlayerCharacter* PlayerCharacter = IGetPlayerCharacter::Execute_GetPlayerCharacter(GetPawn());
	if (PlayerCharacter != nullptr)
		PlayerCharacter->WeaponFireReleased();

	GetWorldTimerManager().ClearTimer(WeaponFireHeldTimer);
}

void APlayerControllerGEP::Sprint()
{
	if (!GetPawn()->GetClass()->ImplementsInterface(UGetPlayerCharacter::StaticClass()))
		return;
					
	APlayerCharacter* PlayerCharacter = IGetPlayerCharacter::Execute_GetPlayerCharacter(GetPawn());
	if (PlayerCharacter != nullptr)
		PlayerCharacter->Sprint();
}

void APlayerControllerGEP::Jump()
{
	if (!GetPawn()->GetClass()->ImplementsInterface(UGetPlayerCharacter::StaticClass()))
		return;
					
	APlayerCharacter* PlayerCharacter = IGetPlayerCharacter::Execute_GetPlayerCharacter(GetPawn());
	if (PlayerCharacter != nullptr)
		PlayerCharacter->Jump();
}

void APlayerControllerGEP::CrouchTriggered()
{
	if (!GetPawn()->GetClass()->ImplementsInterface(UGetPlayerCharacter::StaticClass()))
		return;
					
	APlayerCharacter* PlayerCharacter = IGetPlayerCharacter::Execute_GetPlayerCharacter(GetPawn());
	if (PlayerCharacter != nullptr)
		PlayerCharacter->CrouchTriggered();
}

void APlayerControllerGEP::CheckForInteraction()
{
	UWorld* const World = GetWorld();
	if (!World) return;

	// Line Trace Arguments
    FHitResult Hit;
	const FVector Forward = UGameplayStatics::GetPlayerController(World, 0)->PlayerCameraManager->GetActorForwardVector();
	const FVector Start = UGameplayStatics::GetPlayerController(World, 0)->PlayerCameraManager->GetCameraLocation();
	FVector End = Start + (Forward * 15000.0f);

	// Line trace from camera outwards
	const bool TraceHit = World->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility);
	
	if (!TraceHit || Hit.GetActor() == nullptr)
	{
		ActorToInteractWith = nullptr;
		return;
	}
	
	if (!Hit.GetActor()->GetClass()->ImplementsInterface(UInteractable::StaticClass()))
	{
		ActorToInteractWith = nullptr;
		return;
	}

	// Set actor to interact with
	if (ActorToInteractWith == nullptr && ActorToInteractWith != Hit.GetActor())
		ActorToInteractWith = Hit.GetActor();
}

void APlayerControllerGEP::Interact()
{
	if (ActorToInteractWith == nullptr)
		return;
	
	if (!ActorToInteractWith->GetClass()->ImplementsInterface(UInteractable::StaticClass()))
		return;

	IInteractable::Execute_Interact(ActorToInteractWith);
}
