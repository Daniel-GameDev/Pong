// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "Common/ArenaSides.h"
#include "PlayerCamera.generated.h"


UCLASS()
class PONG_API APlayerCamera : public ACameraActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<ArenaSides> ArenaSide;
	
};
