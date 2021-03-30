// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerControllerGEP.h"



#include "GameFramework/GameModeBase.h"
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
}

void APlayerControllerGEP::BeginPlay()
{
	
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
}

void APlayerControllerGEP::WeaponFireReleased()
{
	if (!GetPawn()->GetClass()->ImplementsInterface(UGetPlayerCharacter::StaticClass()))
		return;
					
	APlayerCharacter* PlayerCharacter = IGetPlayerCharacter::Execute_GetPlayerCharacter(GetPawn());
	if (PlayerCharacter != nullptr)
		PlayerCharacter->WeaponFireReleased();
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
