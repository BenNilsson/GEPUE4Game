#pragma once

#include "CoreMinimal.h"

#include "GEPProjectUE/Public/Player/PlayerControllerCPP.h"
#include "Runtime/Engine/Classes/Animation/AnimInstance.h"
#include "UAnimInstancePlayer.generated.h"

UCLASS(Transient, Blueprintable, HideCategories=AnimInstance, BlueprintType)
class UAnimInstancePlayer : public UAnimInstance
{
	GENERATED_BODY()

public:
	UAnimInstancePlayer();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Generic")
	APlayerControllerCPP* PlayerControllerInstance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Generic")
	float Speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Generic")
	bool IsInAir;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Generic")
	bool IsCrouching;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativeBeginPlay() override;
private:
	

};
