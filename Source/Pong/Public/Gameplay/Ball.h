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

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, 
		class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* BallMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector Direction;

	UPROPERTY(EditAnywhere)
	float BallVelocity;

	UFUNCTION(BlueprintCallable)
	void BallOffset(float deltatime);

	UFUNCTION(BlueprintCallable)
	void ChangeDirectionBasedOnWallType(AActor* TouchedWall);

	UFUNCTION(BlueprintCallable)
	void ChangeSide();

	UFUNCTION(BlueprintCallable)
	void ChangeDirection();
};
