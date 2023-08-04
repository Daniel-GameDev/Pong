// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Common/Walls.h"
#include "Common/WallsInterface.h"
#include "Wall.generated.h"

UCLASS()
class PONG_API AWall : public AActor, public IWallsInterface
{
	GENERATED_BODY()
	
public:
	AWall();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* WallMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<EWallType> WallType;

public:
	FORCEINLINE virtual EWallType GetWallType() override { return EWallType(WallType); }

};
