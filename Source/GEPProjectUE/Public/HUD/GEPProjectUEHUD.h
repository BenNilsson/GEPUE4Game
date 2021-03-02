// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GEPProjectUEHUD.generated.h"

/**
 * 
 */
UCLASS()
class GEPPROJECTUE_API AGEPProjectUEHUD : public AHUD
{
	GENERATED_BODY()

public:
	AGEPProjectUEHUD();

	/* Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/* Crosshair Asset Pointer */
	class UTexture2D* CrosshairTex;
};
