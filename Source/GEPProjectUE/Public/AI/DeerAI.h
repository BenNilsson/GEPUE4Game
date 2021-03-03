// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GEPProjectUE/Public/AI/AIBase.h"
#include "DeerAI.generated.h"

UCLASS()
class GEPPROJECTUE_API ADeerAI : public AAIBase
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ADeerAI();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
