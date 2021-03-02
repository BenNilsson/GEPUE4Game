// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
UENUM()
enum class EWeapon_Combat_Type
{
	None = 0 		UMETA(DisplayName = "None"),
    Melee = 1		UMETA(DisplayName = "Melee"),
    Ranged = 2		UMETA(DisplayName = "Ranged"),
};

class GEPPROJECTUE_API EnumTest
{
public:
	EnumTest();
	~EnumTest();
};
