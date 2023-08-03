// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Common/Walls.h"
#include "WallsInterface.generated.h"

UINTERFACE(MinimalAPI)
class UWallsInterface : public UInterface
{
	GENERATED_BODY()
};

class PONG_API IWallsInterface
{
	GENERATED_BODY()

	
public:
	UFUNCTION()
	virtual EWallType GetWallType() = 0;
};
