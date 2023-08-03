// Fill out your copyright notice in the Description page of Project Settings.

#include "Framework/PongGameMode.h"
#include "Framework/PongPlayerController.h"
#include "Gameplay/Gates.h"
#include "Player/PongArenaCamera.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
//#include "Templates/SubclassOf.h"

AActor* APongGameMode::GetStartPoint(APongPlayerController* PongPlayer)
{
	//PongPlayers.Add(PongPlayer);
	if (PongPlayers.Num() == 1)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player I Entered the Game as RightPlayer!"));

		SetupPlayerData(RightSide);

	}
	else if (PongPlayers.Num() == 2)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player II Entered the Game as LeftPlayer!"));
	}

	return nullptr;
}

void APongGameMode::SetupPlayerData(ArenaSides arenaSide)
{
	TArray<AActor*> GatesArray;;
	TArray<APongArenaCamera*> CameraArray;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGates::StaticClass(), GatesArray);
};
