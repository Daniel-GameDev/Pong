// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Common/ArenaSides.h"
#include "PongGameMode.generated.h"

class AGates;
class APongArenaCamera;
class APongPlayerController;
class APongPlayerStart;

USTRUCT(BlueprintType)
struct FPongPlayer
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<ArenaSides> ArenaSide;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AGates* PlayerGates;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	APongArenaCamera* PlayerArenaCamera;
};

UCLASS()
class PONG_API APongGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable)
	AActor* GetStartPoint(APongPlayerController* PongPlayer);

	UPROPERTY()
	TMap<APongPlayerController*, FPongPlayer> PongPlayers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> WaitWidget;

	UPROPERTY()
	UUserWidget* WaitWidgetInstance;

	/*UPROPERTY(VisibleInstanceOnly)
	class UWaitWidget* WaitWidget;*/

	/*UPROPERTY()
	UUserWidget* WaitWidgetRef;*/

	UFUNCTION()
	FPongPlayer SetupPlayerData(ArenaSides arenaSide);

	UFUNCTION()
	APongPlayerStart* GetPlayerStart(ArenaSides arenaSide);

	UFUNCTION()
	virtual void PostLogin(APlayerController* NewPlayer) override;

	UFUNCTION()
	void SpawnBall();

	/*UFUNCTION()
	void OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);*/

	UFUNCTION()
	void OnComponentEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, 
		class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void CreateWaitWidget(APongPlayerController* PongPlayer);
};
