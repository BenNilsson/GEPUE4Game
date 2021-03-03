// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AIBase.generated.h"

UCLASS()
class GEPPROJECTUE_API AAIBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAIBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/* MESH */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Mesh;
	
	/* HEALTH */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UHealthComponent* Health;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
