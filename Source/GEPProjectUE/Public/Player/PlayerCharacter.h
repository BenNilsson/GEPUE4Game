// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Character.h"
#include "Interfaces/GetInventory.h"
#include "Interfaces/GetPlayerCharacter.h"
#include "Interfaces/GetPlayerController.h"


#include "PlayerCharacter.generated.h"

class UItem;

UENUM(BlueprintType)
enum EPlayer_Combat_State
{
	Passive 	UMETA(DisplayName = "Passive"),
	Melee		UMETA(DisplayName = "Melee"),
	Ranged		UMETA(DisplayName = "Ranged"),
};

UCLASS()
class GEPPROJECTUE_API APlayerCharacter : public ACharacter, public IGetPlayerCharacter,
public IGetInventory , public IGetPlayerController, public IInitializeable
{
	GENERATED_BODY()

	/* CAMERA BOOM ARM */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoomArm;

	/* CAMERA */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;

	/* HEALTH */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UHealthComponent* Health;
	
	/* INVENTORY */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory", meta = (AllowPrivateAccess = "true"))
	class UInventoryComponent* InventoryComponent;

	/* WEAPON SOCKET */
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* WeaponSocketSceneComponent;

	/* WEAPON */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UChildActorComponent* Weapon;

	/* COMBAT STATE */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TEnumAsByte<EPlayer_Combat_State> EPlayerCombatState;

	/* AIStumuliSourceComponent */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UAIPerceptionStimuliSourceComponent* AIPerceptionStimuliSourceComponent;
	
public:
	// Sets default values for this character's properties
	APlayerCharacter();
	
	/* Use Item */
	UFUNCTION(BlueprintCallable)
	void UseItem(UItem* Item);
	
	UPROPERTY(EditAnywhere, Category="Controller Settings")
	class UAnimInstancePlayer* AnimInstancePlayer;

	/* Weapon Fire Montage */
	UPROPERTY(EditAnywhere)
	class UAnimMontage* WeaponAnimMontage;

	/* Movement Functions */
	UPROPERTY(EditAnywhere, Category="Controller Settings")
	float SprintModifier;
	UPROPERTY(EditAnywhere, Category="Controller Settings")
	float CrouchModifier;

	UPROPERTY(VisibleAnywhere, Category="Controller Settings")
	bool IsSprinting;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Controller Settings")
	float BaseMovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Player")
	class UArrowItem* ArrowItem;
	
	void DoJump();

	/* INTERFACES */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	APlayerCharacter* GetPlayerCharacter();
	virtual APlayerCharacter* GetPlayerCharacter_Implementation() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    class APlayerControllerGEP* GetPlayerControllerGEP();
	virtual class APlayerControllerGEP* GetPlayerControllerGEP_Implementation() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    UInventoryComponent* GetInventory();
	virtual UInventoryComponent* GetInventory_Implementation() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnInitialized(); // BP
	virtual void Initialize_Implementation() override;
	
	void MoveForward(float Value);
	void MoveRight(float Value);

	void LookUp();
	void Turn();
	
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);

	void SetState(EPlayer_Combat_State State);
	
	void WeaponFireTriggered();
	void WeaponFireHeld();
	void WeaponFireReleased();

	void Sprint();
	virtual void Jump() override;
	void CrouchTriggered();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OptionsMenuButtonTriggered();

	bool bIsMouseHeld;
protected:

	UPROPERTY(EditAnywhere, Category="Controller Settings")
	float TurnRate;
	UPROPERTY(EditAnywhere, Category="Controller Settings")
	float LookRate;
	UPROPERTY(VisibleAnywhere, Category="Controller Settings")
	bool IsCrouching;

};
