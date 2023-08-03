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

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<EWallType> WallType;

	virtual EWallType GetWallType() override;

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ChangeSize();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector SideWallSize = FVector(41.f, 1.f, 3.f);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector FrontWallSize = FVector(6.f, 1.f, 3.f);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* WallMesh;
};
