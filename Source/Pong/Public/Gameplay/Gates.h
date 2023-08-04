// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Common/ArenaSides.h"
#include "Gates.generated.h"

class UBoxComponent;

UCLASS()
class PONG_API AGates : public AActor
{
	GENERATED_BODY()
	
public:
	AGates();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<ArenaSides> ArenaSide;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* GatesCollision;

protected:
	virtual void BeginPlay() override;
	
};
