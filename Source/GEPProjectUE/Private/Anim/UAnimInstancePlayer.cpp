
#include "GEPProjectUE/Public/Anim/UAnimInstancePlayer.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Player/PlayerCharacter.h"

UAnimInstancePlayer::UAnimInstancePlayer()
{
	Speed = 0.0f;
	IsInAir = false;
	Speed = 0;
}

void UAnimInstancePlayer::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	if (PlayerControllerInstance != nullptr)
	{
		// Set speed
		Speed = PlayerControllerInstance->GetVelocity().Size();

		IsInAir = PlayerControllerInstance->GetCharacterMovement()->IsFalling();
	}
}

void UAnimInstancePlayer::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	PlayerControllerInstance = Cast<APlayerCharacter>(GetOwningActor());
}


