// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerJumpNotify.h"

void UPlayerJumpNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	PlayerControllerInstance = Cast<APlayerControllerCPP>(MeshComp->GetOwner());
	PlayerControllerInstance->DoJump();
}
