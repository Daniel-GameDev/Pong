// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Common/ArenaSides.h"
#include "PongGameMode.generated.h"

class AGates;
class APongArenaCamera;
class APongPlayerController;

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

	UFUNCTION()
	void SetupPlayerData(ArenaSides arenaSide);
};
