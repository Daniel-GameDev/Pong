// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Common/ArenaSides.h"
#include "PongPlayerController.generated.h"

//class APongArenaCamera;

UCLASS()
class PONG_API APongPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	APongPlayerController();

	virtual void SetupInputComponent() override;

	UFUNCTION(BlueprintCallable)
	void MovePlatform(float Value);

	//TODO: Switch speed input for sides on begin play
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<EArenaSides> ArenaSide;

	UPROPERTY(EditAnywhere)
	float PlatformVelocity;

	UPROPERTY(EditAnywhere)
	float MinRange;

	UPROPERTY(EditAnywhere)
	float MaxRange;

	//UPROPERTY(EditAnywhere)
	//APongArenaCamera* PongArenaCamera;

	//UFUNCTION(BlueprintCallable)
	//void SetupPlayerCamera(APongArenaCamera* PongArenaCamera);

	UFUNCTION(Server, Unreliable)
	void AddPlatformOffSet(float deltaY);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	UUserWidget* ScoretWidget;

	//UFUNCTION(BlueprintImplementableEvent, Client, Unreliable)
	//void DoSomething2();

private:
	UPROPERTY()
	float DeltaLocation;
};
