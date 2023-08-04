// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ball.generated.h"

UCLASS()
class PONG_API ABall : public AActor
{
	GENERATED_BODY()
	
public:
	ABall();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* BallMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector Direction;

	UPROPERTY(EditAnywhere)
	float Velocity;

	UFUNCTION(BlueprintCallable)
	void Offset(float deltatime);

	UFUNCTION(BlueprintCallable)
	void ChangeSide();

	UFUNCTION(BlueprintCallable)
	void ChangeDirection();

	UFUNCTION(BlueprintCallable)
	void ChangeDirectionByWallType(AActor* TouchedWall);

private:
	void SetRandomDirection();

public:
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
