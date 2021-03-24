// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerControllerGEP.generated.h"

/**
 * 
 */
UCLASS()
class GEPPROJECTUE_API APlayerControllerGEP : public APlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<APawn> PawnToPossess;
	
private:
	// Called to bind functionality to input
	virtual void SetupInputComponent() override;

	virtual void BeginPlay() override;
	
	void MoveForward(float Value);
	void MoveRight(float Value);

	void LookUp(float Value);
	void Turn(float Value);
	
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);
	
	void WeaponFireTriggered();
	void WeaponFireReleased();

	void Sprint();
	void Jump();
	void CrouchTriggered();

public:
	
	APlayerControllerGEP();
};
