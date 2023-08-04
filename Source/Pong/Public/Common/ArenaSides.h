// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ArenaSides.generated.h"

UENUM(BlueprintType)
enum EArenaSides
{
	EAS_RightSide UMETA(DisplayName = "EAS_RightSide"),
	EAS_LeftSide UMETA(DisplayName = "EAS_LeftSide")
};