// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerControllerCPP.h"
#include "Anim/UAnimInstancePlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Inventory/Item.h"
#include "Inventory/InventoryComponent.h"
#include "Components/HealthComponent.h"
#include "WeaponCombatTypeEnum.h"
#include "Interfaces/Fireable.h"
#include "Interfaces/Weaponable.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"

// Sets default values
APlayerControllerCPP::APlayerControllerCPP()
{
	// Create Camera Boom arm
	CameraBoomArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoomArm")); // Create a USpringArmComponent
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

	// Health Component
	Health = CreateDefaultSubobject<UHealthComponent>("PlayerHealth");
	
	// Player Inventory
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>("PlayerInventory");
	InventoryComponent->MaxSize = 32;

	// Weapon Socket
	WeaponSocketSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("WeaponSocketSceneComponent"));
	WeaponSocketSceneComponent->SetupAttachment(ACharacter::GetMesh(), "WeaponSocket_R");
	
	// Weapon
	Weapon = CreateDefaultSubobject<UChildActorComponent>(TEXT("WeaponSlot"));
	Weapon->SetupAttachment(WeaponSocketSceneComponent);
	Weapon->CreateChildActor();

	// AIPerceptionStimuliSourceComponent
	AIPerceptionStimuliSourceComponent = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("AIPerceptionStimuliSourceComponent"));
	
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

APlayerControllerCPP* APlayerControllerCPP::GetPlayerController_Implementation()
{
	return this;
}

UInventoryComponent* APlayerControllerCPP::GetInventory_Implementation()
{
	return InventoryComponent;
}

// Called when the game starts or when spawned
void APlayerControllerCPP::BeginPlay()
{
	Super::BeginPlay();

	// Set Anim Instance
	AnimInstancePlayer = Cast<UAnimInstancePlayer>(GetMesh()->GetAnimInstance());

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
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &APlayerControllerCPP::Sprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &APlayerControllerCPP::Sprint);
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &APlayerControllerCPP::CrouchTriggered);

	// Weapon Fire Actions
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APlayerControllerCPP::WeaponFireTriggered);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &APlayerControllerCPP::WeaponFireReleased);
	
	
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

void APlayerControllerCPP::SetState(EPlayer_Combat_State State)
{
	EPlayerCombatState = State;

	switch (State)
	{
		case Melee:
			bUseControllerRotationYaw = false;
			break;
		case Ranged:
			// Don't rotate camera mesh, only the camera
			bUseControllerRotationYaw = true;
			break;
		case Passive:
			bUseControllerRotationYaw = false;
			break;
		default:
			break;
	}
}

void APlayerControllerCPP::WeaponFireTriggered()
{
	if (Weapon == nullptr) return;
	
	AActor* WeaponChildActor = Weapon->GetChildActor();

	// Change state depending on weapon type
	if (WeaponChildActor->GetClass()->ImplementsInterface(UWeaponable::StaticClass()))
	{
		const EWeapon_Combat_Type WeaponType = IWeaponable::Execute_GetWeaponType(WeaponChildActor);
		switch (WeaponType)
		{
			case EWeapon_Combat_Type::Melee:
				SetState(Melee);
				break;
			case EWeapon_Combat_Type::Ranged:
				SetState(Ranged);
				break;
			case EWeapon_Combat_Type::None:
				SetState(Passive);
				break;
			default:
				break;
		}
		
	}
	
	if (WeaponChildActor->GetClass()->ImplementsInterface(UFireable::StaticClass()))
		IFireable::Execute_Fire(WeaponChildActor);

	if (WeaponAnimMontage)
		PlayAnimMontage(WeaponAnimMontage);
	
}

void APlayerControllerCPP::WeaponFireReleased()
{
	if (Weapon == nullptr || EPlayerCombatState == Passive) return;

	AActor* WeaponChildActor = Weapon->GetChildActor();

	switch (EPlayerCombatState)
	{
	    case Ranged:
	    	if (WeaponAnimMontage)
	    		StopAnimMontage(WeaponAnimMontage);
			break;
		default:
			break;
	}

	SetState(Passive);

	if (WeaponChildActor->GetClass()->ImplementsInterface(UFireable::StaticClass()))
		IFireable::Execute_FireReleased(WeaponChildActor);
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