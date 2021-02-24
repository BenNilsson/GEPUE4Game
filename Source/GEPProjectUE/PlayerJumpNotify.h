// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "PlayerControllerCPP.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "PlayerJumpNotify.generated.h"

/**
 * 
 */

class APlayerControllerCPP;

UCLASS()
class GEPPROJECTUE_API UPlayerJumpNotify : public UAnimNotify
{
	GENERATED_BODY()

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	UPROPERTY(VisibleAnywhere, Category="Generic")
	APlayerControllerCPP* PlayerControllerInstance;
};
