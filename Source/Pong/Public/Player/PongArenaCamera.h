// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "Common/ArenaSides.h"
#include "PongArenaCamera.generated.h"

UCLASS()
class PONG_API APongArenaCamera : public ACameraActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<EArenaSides> ArenaSide;
};
