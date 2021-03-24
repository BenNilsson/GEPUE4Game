// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHealthBelow0);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GEPPROJECTUE_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	FHealthBelow0 OnHealthBelowZero;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HealthStart;

	UPROPERTY(BlueprintReadOnly)
	float Health;
	
	UFUNCTION(BlueprintCallable)
	virtual void TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
};
