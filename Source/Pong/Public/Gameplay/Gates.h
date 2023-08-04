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

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* GatesCollision;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<EArenaSides> ArenaSide;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
