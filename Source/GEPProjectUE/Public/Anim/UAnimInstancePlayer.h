#pragma once

#include "CoreMinimal.h"

#include "Player/PlayerCharacter.h"
#include "Runtime/Engine/Classes/Animation/AnimInstance.h"
#include "UAnimInstancePlayer.generated.h"

UCLASS(Transient, Blueprintable, HideCategories=AnimInstance, BlueprintType)
class UAnimInstancePlayer : public UAnimInstance
{
	GENERATED_BODY()

public:
	UAnimInstancePlayer();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Generic")
	APlayerCharacter* PlayerControllerInstance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Generic")
	float Speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Generic")
	bool IsInAir;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Generic")
	bool IsCrouching;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativeBeginPlay() override;

};
