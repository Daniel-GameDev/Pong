// Fill out your copyright notice in the Description page of Project Settings.

#include "Framework/PongGameMode.h"
#include "Framework/PongPlayerController.h"
#include "Gameplay/Gates.h"
#include "Player/PongArenaCamera.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PongPlayerStart.h"
#include "Camera/CameraActor.h"

AActor* APongGameMode::GetStartPoint(APongPlayerController* PongPlayer)
{
	if (PongPlayers.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player I Entered the Game as RightPlayer!"));

		PongPlayers.Add(PongPlayer, SetupPlayerData(RightSide));

		return GetPlayerStart(RightSide);
		
	}
	else if (PongPlayers.Num() == 1)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player II Entered the Game as LeftPlayer!"));

		PongPlayers.Add(PongPlayer, SetupPlayerData(LeftSide));

		return GetPlayerStart(LeftSide);
	}

	return nullptr;
}

FPongPlayer APongGameMode::SetupPlayerData(ArenaSides arenaSide)
{
	TArray<AActor*> GatesArray;;
	TArray<AActor*> CameraArray;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGates::StaticClass(), GatesArray);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APongArenaCamera::StaticClass(), CameraArray);

	FPongPlayer PongPlayerTempStruct;
	PongPlayerTempStruct.ArenaSide = arenaSide;

	for (AActor* TGates : GatesArray)
	{
		AGates* Gate = Cast<AGates>(TGates);

		if (Gate != nullptr)
		{
			if ((Gate->ArenaSide) == arenaSide)
			{
				PongPlayerTempStruct.PlayerGates = Gate;
			}
		}
	}

	for (AActor* TPongCamera : CameraArray)
	{
		APongArenaCamera* PongCam = Cast<APongArenaCamera>(TPongCamera);

		if (PongCam != nullptr)
		{
			if ((PongCam->ArenaSide) == arenaSide)
			{
				PongPlayerTempStruct.PlayerArenaCamera = PongCam;
			}
		}
	}

	return PongPlayerTempStruct;
}
APongPlayerStart* APongGameMode::GetPlayerStart(ArenaSides arenaSide)
{
	APongPlayerStart* TempPlayerStart = nullptr;
	TArray<AActor*> GameStarArray;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APongPlayerStart::StaticClass(), GameStarArray);

	for (AActor* TStartPoint : GameStarArray)
	{
		APongPlayerStart* PlayerStart = Cast<APongPlayerStart>(TStartPoint);

		if (PlayerStart != nullptr)
		{
			if ((PlayerStart->ArenaSide) == arenaSide)
			{
				TempPlayerStart = PlayerStart;
			}
		}
	}

	return TempPlayerStart;
}
void APongGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	APongPlayerController* NewPongPlayer = Cast<APongPlayerController>(NewPlayer);

	if (PongPlayers.Contains(NewPongPlayer))
	{
		NewPongPlayer->SetViewTargetWithBlend(PongPlayers.Find(NewPongPlayer)->PlayerArenaCamera);
	}
};
