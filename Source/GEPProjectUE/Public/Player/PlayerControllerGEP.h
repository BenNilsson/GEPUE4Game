// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Interfaces/GetPlayerController.h"

#include "PlayerControllerGEP.generated.h"

/**
 * 
 */
UCLASS()
class GEPPROJECTUE_API APlayerControllerGEP : public APlayerController, public IGetPlayerController, public IInitializeable
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<APawn> PawnToPossess;

	UPROPERTY()
	AActor* ActorToInteractWith;
	
private:
	// Called to bind functionality to input
	virtual void SetupInputComponent() override;
	
	void MoveForward(float Value);
	void MoveRight(float Value);

	void LookUp(float Value);
	void Turn(float Value);
	
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);
	
	void WeaponFireTriggered();
	FTimerHandle WeaponFireHeldTimer;
	void WeaponFireHeld();
	void WeaponFireReleased();

	void Sprint();
	void Jump();
	void CrouchTriggered();

    void OptionsMenuButtonTriggered();
	

	void CheckForInteraction();
	FTimerHandle InteractionTimer;
	void Interact();

public:
	
	APlayerControllerGEP();

	virtual APlayerControllerGEP* GetPlayerControllerGEP_Implementation() override;

	virtual void Initialize_Implementation() override;
	UFUNCTION(BlueprintImplementableEvent)
    void ReceiveInitialized();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void OnOptionsMenuPressed();
};
