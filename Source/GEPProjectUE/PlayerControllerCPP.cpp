// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllerCPP.h"

#include "Anim/UAnimInstancePlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Interfaces/Fireable.h"
#include "Inventory/Item.h"
#include "Inventory/InventoryComponent.h"

// Sets default values
APlayerControllerCPP::APlayerControllerCPP()
{
	// Create Camera Boom arm
	CameraBoomArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom Arm")); // Create a USpringArmComponent
	CameraBoomArm->SetupAttachment(RootComponent); // Attach it as the Root component
	CameraBoomArm->TargetArmLength = 600; // Set length (how far back the camera is)
	CameraBoomArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraBoomArm, USpringArmComponent::SocketName); // Attach to Camera boom arm's socket
	Camera->bUsePawnControlRotation = false; // Don't rotate camera relatively to the boom arm.

	// Don't rotate camera mesh, only the camera
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Rotates the character towards the direction of acceleration
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0, 540, 0);

	// Player Inventory
	Inventory = CreateDefaultSubobject<UInventoryComponent>("PlayerInventory");

	// Weapon Socket
	WeaponSocketSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Weapon Socket Scene Component"));
	WeaponSocketSceneComponent->SetupAttachment(ACharacter::GetMesh(), "WeaponSocket_R");
	
	// Weapon
	Weapon = CreateDefaultSubobject<UChildActorComponent>(TEXT("WeaponSlot"));
	Weapon->SetupAttachment(WeaponSocketSceneComponent);
	Weapon->CreateChildActor();
	
	// Set Base Controller Values
	IsSprinting = false;
}

void APlayerControllerCPP::UseItem(UItem* Item)
{
	if (Item)
	{
		Item->Use(this);
		Item->UseBP(this);
	}
}

void APlayerControllerCPP::DoJump()
{
	ACharacter::Jump();
}

// Called when the game starts or when spawned
void APlayerControllerCPP::BeginPlay()
{
	Super::BeginPlay();

	// Set Anim Instance
	AnimInstancePlayer = Cast<UAnimInstancePlayer>(ACharacter::GetMesh()->GetAnimInstance());

	// Set walk speed
	GetCharacterMovement()->MaxWalkSpeed = BaseMovementSpeed;
}

// Called to bind functionality to input
void APlayerControllerCPP::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	// Bind Mapping Axis' to functions defined
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerControllerCPP::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerControllerCPP::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &APlayerControllerCPP::LookUpAtRate);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &APlayerControllerCPP::TurnAtRate);

	// Bind Mapping Actions
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Pressed, this, &APlayerControllerCPP::Sprint);
	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Released, this, &APlayerControllerCPP::Sprint);
	PlayerInputComponent->BindAction("Crouch", EInputEvent::IE_Pressed, this, &APlayerControllerCPP::CrouchTriggered);

	// Weapon Fire Actions
	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &APlayerControllerCPP::WeaponFireTriggered);
	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Released, this, &APlayerControllerCPP::WeaponFireReleased);
	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Repeat, this, &APlayerControllerCPP::WeaponFireHeld);
	
	
	TurnRate = 80;
	LookRate = 80;
}

void APlayerControllerCPP::MoveForward(float Value)
{
	if (Controller != nullptr && Value != 0.0)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator Yaw(0, Rotation.Yaw, 0);

		// Get forward vector
		const FVector Direction = FRotationMatrix(Yaw).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void APlayerControllerCPP::MoveRight(float Value)
{
	if (Controller != nullptr && Value != 0.0)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator Yaw(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(Yaw).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void APlayerControllerCPP::TurnAtRate(float Rate)
{
	if (Controller != nullptr && Rate != 0.0)	
		AddControllerYawInput(Rate * GetWorld()->GetDeltaSeconds() * TurnRate);
}

void APlayerControllerCPP::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * GetWorld()->GetDeltaSeconds() * LookRate);
}

void APlayerControllerCPP::WeaponFireTriggered()
{
	if (Weapon == nullptr) return;
	
	AActor* WeaponChildActor = Weapon->GetChildActor();
	IFireable* WeaponCast = Cast<IFireable>(WeaponChildActor);

	if (WeaponAnimMontage)
		PlayAnimMontage(WeaponAnimMontage);
	
	if (WeaponCast)
		WeaponCast->Execute_Fire(WeaponChildActor);
}

void APlayerControllerCPP::WeaponFireReleased()
{
	if (Weapon == nullptr) return;

	if (WeaponAnimMontage)
		StopAnimMontage(WeaponAnimMontage);
	
	AActor* WeaponChildActor = Weapon->GetChildActor();
	IFireable* WeaponCast = Cast<IFireable>(WeaponChildActor);
	
	if (WeaponCast)
		WeaponCast->Execute_FireReleased(WeaponChildActor);
}

void APlayerControllerCPP::WeaponFireHeld()
{
	if (Weapon == nullptr) return;

	AActor* weaponChildActor = Weapon->GetChildActor();
	IFireable* weaponCast = Cast<IFireable>(weaponChildActor);
	
	if (weaponCast)
		weaponCast->Execute_FireHeld(weaponChildActor);
}

void APlayerControllerCPP::Sprint()
{
	if (IsCrouching) return;

	IsSprinting = !IsSprinting;
	GetCharacterMovement()->MaxWalkSpeed = IsSprinting ? BaseMovementSpeed * SprintModifier : BaseMovementSpeed;
}

void APlayerControllerCPP::CrouchTriggered()
{
	if (!IsCrouching)
	{
		if (IsSprinting)
			// Force the player to stop sprinting
			IsSprinting = false;
		
		Crouch();
		GetCharacterMovement()->MaxWalkSpeed = BaseMovementSpeed * CrouchModifier;
	}else
	{
		UnCrouch();
		GetCharacterMovement()->MaxWalkSpeed = BaseMovementSpeed;
	}
	
	IsCrouching = !IsCrouching;
	AnimInstancePlayer->IsCrouching = IsCrouching;
}