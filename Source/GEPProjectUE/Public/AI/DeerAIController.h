// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "DeerAIController.generated.h"

/**
 * 
 */
UCLASS()
class GEPPROJECTUE_API ADeerAIController : public AAIController
{
	GENERATED_BODY()

	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

public:
	ADeerAIController();
	
protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UAIPerceptionComponent* AIPerceptionComponent;
	
};
