// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "PickupBase.generated.h"

UCLASS()
class GEPPROJECTUE_API APickupBase : public AActor
{
	GENERATED_BODY()

protected:
	
	/* Scene Component */
	UPROPERTY(EditAnywhere, Category="Pickup")
	class USceneComponent* SceneComponent;
	
	/* Mesh */
	UPROPERTY(EditAnywhere, Category="Pickup")
	UStaticMeshComponent* Mesh;
	
	/* Overlap Sphere Component */
	UPROPERTY(VisibleAnywhere, Category="Pickup")
	USphereComponent* SphereComponent;
	
public:	
	// Sets default values for this actor's properties
	APickupBase();

	/* Overlap Enter */
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	UFUNCTION(BlueprintNativeEvent, Category="Pickup")
	void OnActivate(AActor* PickedUpBy);
	virtual void OnActivate_Implementation(AActor* PickedUpBy);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
};
