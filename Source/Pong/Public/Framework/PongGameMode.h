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
class UUserWidget;
class ABall;

USTRUCT(BlueprintType)
struct FPongPlayer
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EArenaSides> ArenaSide;

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
	UPROPERTY(EditAnywhere)
	UBlueprint* Ball;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TMap<APongPlayerController*, FPongPlayer> PongPlayers;

	UFUNCTION(BlueprintCallable)
	AActor* GetStartPoint(APongPlayerController* PongPlayer);

	UFUNCTION(BlueprintCallable)
	FPongPlayer SetupPlayerData(EArenaSides PlayerSide);

	UFUNCTION(BlueprintCallable)
	APongPlayerStart* GetPlayerStart(EArenaSides PlayerSide);

	UFUNCTION(BlueprintCallable)
	virtual void PostLogin(APlayerController* NewPlayer) override;

	UFUNCTION(BlueprintCallable)
	void SpawnBall();

	UFUNCTION(BlueprintImplementableEvent)
	void AddScore(APlayerController* PongPlayer, EArenaSides PlayerSide);

	UFUNCTION()
	void OnComponentEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, 
		class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
