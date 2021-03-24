// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Character.h"
#include "Interfaces/GetBaseAI.h"
#include "AIBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);

UCLASS()
class GEPPROJECTUE_API AAIBase : public ACharacter, public IGetBaseAI
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAIBase();

	UPROPERTY(EditDefaultsOnly, BluePrintReadOnly)
	class UBehaviorTree* BehaviorTree;

	FOnDeath OnDeath;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
		
	/* HEALTH */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UHealthComponent* Health;

	UFUNCTION(BlueprintCallable)
	virtual void AIDied();
	
public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/* INTERFACES */
	virtual AAIBase* GetAIBase_Implementation() override { return this; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float WalkingSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RunningSpeed;

};
