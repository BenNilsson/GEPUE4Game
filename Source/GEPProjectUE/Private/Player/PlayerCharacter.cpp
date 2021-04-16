// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/PlayerCharacter.h"
#include "Anim/UAnimInstancePlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Inventory/Item.h"
#include "Inventory/InventoryComponent.h"
#include "Components/HealthComponent.h"
#include "WeaponCombatTypeEnum.h"
#include "Interfaces/Fireable.h"
#include "Interfaces/GetWeaponBow.h"
#include "Interfaces/Weaponable.h"
#include "Inventory/ArrowItem.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Weaponry/WeaponBow.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
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

	TurnRate = 80;
	LookRate = 80;
}

void APlayerCharacter::UseItem(UItem* Item)
{
	if (Item)
	{
		Item->Use(this);
		Item->UseBP(this);
	}
}

void APlayerCharacter::DoJump()
{
	ACharacter::Jump();
}

APlayerCharacter* APlayerCharacter::GetPlayerCharacter_Implementation()
{
	return this;
}

APlayerControllerGEP* APlayerCharacter::GetPlayerControllerGEP_Implementation()
{
	if (!Controller)
		return nullptr;
	
	if (Controller->GetClass()->ImplementsInterface(UGetPlayerController::StaticClass()))
	{
		APlayerControllerGEP* PlayerController = IGetPlayerController::Execute_GetPlayerControllerGEP(Controller);
		if (PlayerController)
			return PlayerController;
	}
	
	return nullptr;
}


UInventoryComponent* APlayerCharacter::GetInventory_Implementation()
{
	return InventoryComponent;
}

void APlayerCharacter::Initialize_Implementation()
{
	// Health Component
	if (Health->GetClass()->ImplementsInterface(UInitializeable::StaticClass()))
	{
		IInitializeable::Execute_Initialize(Health);
		// Death Event
	}
	
	// Set Anim Instance
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance)
		AnimInstancePlayer = Cast<UAnimInstancePlayer>(AnimInstance);

	if (AnimInstancePlayer)
	{
		// Set walk speed
		GetCharacterMovement()->MaxWalkSpeed = BaseMovementSpeed;

		IsSprinting = false;
	}
}


void APlayerCharacter::MoveForward(float Value)
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

void APlayerCharacter::MoveRight(float Value)
{
	if (Controller != nullptr && Value != 0.0)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator Yaw(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(Yaw).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacter::LookUp()
{
}

void APlayerCharacter::Turn()
{
}

void APlayerCharacter::TurnAtRate(float Rate)
{
	if (Controller != nullptr && Rate != 0.0)	
		AddControllerYawInput(Rate * GetWorld()->GetDeltaSeconds() * TurnRate);
}

void APlayerCharacter::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * GetWorld()->GetDeltaSeconds() * LookRate);
}

void APlayerCharacter::SetState(EPlayer_Combat_State State)
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

void APlayerCharacter::WeaponFireTriggered()
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
			{
				if (!ArrowItem)
					ArrowItem = InventoryComponent->GetArrow();
				else if (!InventoryComponent->ContainsItem(ArrowItem))
					ArrowItem = InventoryComponent->GetArrow();
					
				if (!ArrowItem)
					return;
					
				// Get Bow & Change Arrow Type
				if (!WeaponChildActor->GetClass()->ImplementsInterface(UGetWeaponBow::StaticClass()))
					return;
					
				AWeaponBow* Bow = IGetWeaponBow::Execute_GetWeaponBow(WeaponChildActor);

				if (!Bow)
					return;

				Bow->ArrowProjectile = ArrowItem->ArrowProjectile;
				SetState(Ranged);
				break;
			}
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

void APlayerCharacter::WeaponFireHeld()
{
	if (Weapon == nullptr || EPlayerCombatState == Passive) return;

	AActor* WeaponChildActor = Weapon->GetChildActor();
	
	if (WeaponChildActor->GetClass()->ImplementsInterface(UFireable::StaticClass()))
		IFireable::Execute_FireHeld(WeaponChildActor);
}

void APlayerCharacter::WeaponFireReleased()
{
	if (Weapon == nullptr || EPlayerCombatState == Passive) return;

	AActor* WeaponChildActor = Weapon->GetChildActor();

	if (WeaponChildActor->GetClass()->ImplementsInterface(UFireable::StaticClass()))
	{
		if (IFireable::Execute_FireReleased(WeaponChildActor))
		{
			switch (EPlayerCombatState)
			{
			case Ranged:
				if (!ArrowItem)
					ArrowItem = InventoryComponent->GetArrow();
				else if (!InventoryComponent->ContainsItem(ArrowItem))
					ArrowItem = InventoryComponent->GetArrow();
		
				if (!ArrowItem)
					return;

				InventoryComponent->RemoveItem(ArrowItem);
				break;
			default:
				break;
			}
		}

		// Stop animations and change state
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
	}
}

void APlayerCharacter::Sprint()
{
	if (IsCrouching) return;

	IsSprinting = !IsSprinting;
	GetCharacterMovement()->MaxWalkSpeed = IsSprinting ? BaseMovementSpeed * SprintModifier : BaseMovementSpeed;
}

void APlayerCharacter::Jump()
{
	ACharacter::Jump();
}

void APlayerCharacter::CrouchTriggered()
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
	if (AnimInstancePlayer)
		AnimInstancePlayer->IsCrouching = IsCrouching;
}