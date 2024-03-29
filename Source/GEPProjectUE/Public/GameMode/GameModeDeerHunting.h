// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Interaction/StartGameButton.h"

#include "GameModeDeerHunting.generated.h"

UCLASS()
class GEPPROJECTUE_API AGameModeDeerHunting : public AGameModeBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	AStartGameButton* StartGameButton;
	
	UPROPERTY(EditDefaultsOnly)
	int DeerAmountKilledToWin;
	
	UPROPERTY(EditDefaultsOnly)
	class TSubclassOf<class ADeerSpawner> ActorSpawnerToSpawn;

	UPROPERTY(VisibleAnywhere)
	class ADeerSpawner* ActorSpawner;

	int DeersKilled;

public:
	AGameModeDeerHunting();

	virtual AActor* FindPlayerStart_Implementation(AController* Player, const FString& IncomingName) override;

	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY()
	TArray<AActor*> PlayerStarts;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<AController*> PlayerControllers;

private:
	
	UFUNCTION()
	void OnActorKilled(AActor* ActorDied);

	UFUNCTION()
	void StartButtonClicked(bool Active);
	UFUNCTION()
	void StartGame();
	UFUNCTION()
	void EndGame(bool Victory);
	UFUNCTION()
	void CreateSpawner();
};
