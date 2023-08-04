// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Common/ArenaSides.h"
#include "PongPlayerController.generated.h"

UCLASS()
class PONG_API APongPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	APongPlayerController();

	virtual void SetupInputComponent() override;

	UFUNCTION(BlueprintCallable)
	void MovePlatform(float Value);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<EArenaSides> ArenaSide;

	UPROPERTY(EditAnywhere)
	float PlatformVelocity;

	UPROPERTY(EditAnywhere)
	float MinRange;

	UPROPERTY(EditAnywhere)
	float MaxRange;

	UFUNCTION(Server, Unreliable)
	void AddPlatformOffSet(float DeltaY);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	UUserWidget* ScoretWidget;

private:
	UPROPERTY()
	float DeltaLocation;
};
