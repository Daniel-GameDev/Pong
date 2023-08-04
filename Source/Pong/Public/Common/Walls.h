// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Walls.generated.h"

UENUM(BlueprintType)
enum EWallType
{
	EWT_Side UMETA(DisplayName = "Side"),
	EWT_Front UMETA(DisplayName = "Front")
};
