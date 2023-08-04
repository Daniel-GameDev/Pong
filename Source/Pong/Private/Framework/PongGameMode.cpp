// Fill out your copyright notice in the Description page of Project Settings.

#include "Framework/PongGameMode.h"
#include "Framework/PongPlayerController.h"
#include "Gameplay/Gates.h"
#include "Player/PongArenaCamera.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PongPlayerStart.h"
#include "Camera/CameraActor.h"
#include "Gameplay/Ball.h"
#include "Components/BoxComponent.h"
#include "Blueprint/UserWidget.h"
#include "Gameplay/Ball.h"

AActor* APongGameMode::GetStartPoint(APongPlayerController* PongPlayer)
{
	if (PongPlayers.Num() == 0)
	{
		PongPlayers.Add(PongPlayer, SetupPlayerData(EAS_RightSide));

		PongPlayer->PlatformVelocity = PongPlayer->PlatformVelocity * -1;

		return GetPlayerStart(EAS_RightSide);
	}
	else if (PongPlayers.Num() == 1)
	{
		PongPlayers.Add(PongPlayer, SetupPlayerData(EAS_LeftSide));

		return GetPlayerStart(EAS_LeftSide);
	}

	return nullptr;
}

FPongPlayer APongGameMode::SetupPlayerData(EArenaSides PlayerSide)
{
	TArray<AActor*> GatesArray;;
	TArray<AActor*> CameraArray;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGates::StaticClass(), GatesArray);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APongArenaCamera::StaticClass(), CameraArray);

	FPongPlayer PongPlayerTempStruct;
	PongPlayerTempStruct.ArenaSide = PlayerSide;

	for (AActor* TGates : GatesArray)
	{
		if (AGates* Gate = Cast<AGates>(TGates))
		{
 			if (Gate->ArenaSide == PlayerSide)
			{
				PongPlayerTempStruct.PlayerGates = Gate;
				break;
			}
		}
	}

	for (AActor* TPongCamera : CameraArray)
	{
		if (APongArenaCamera* PongCam = Cast<APongArenaCamera>(TPongCamera))
		{
			if (PongCam->ArenaSide == PlayerSide)
			{
				PongPlayerTempStruct.PlayerArenaCamera = PongCam;
				break;
			}
		}
	}

	return PongPlayerTempStruct;
}

APongPlayerStart* APongGameMode::GetPlayerStart(EArenaSides PlayerSide)
{
	APongPlayerStart* TempPlayerStart = nullptr;
	TArray<AActor*> GameStarArray;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APongPlayerStart::StaticClass(), GameStarArray);

	for (AActor* TStartPoint : GameStarArray)
	{
		if (APongPlayerStart* PlayerStart = Cast<APongPlayerStart>(TStartPoint))
		{
			if (PlayerStart->ArenaSide == PlayerSide)
			{
				TempPlayerStart = PlayerStart;
				break;
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

		PongPlayers.Find(NewPongPlayer)->PlayerGates->GatesCollision->OnComponentEndOverlap.AddDynamic(this, &APongGameMode::OnComponentEndOverlap);
	}
}

void APongGameMode::SpawnBall()
{
	FVector Location(0.f, 0.f, 200.f);
	FRotator Rotation(0.f, 0.f, 0.f);

	if (Ball)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		GetWorld()->SpawnActor<AActor>(Ball->GeneratedClass, Location, Rotation, SpawnParams);
	}
}

void APongGameMode::OnComponentEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (AGates* Gates = Cast<AGates>(OverlappedComp->GetOwner()))
	{
		for (auto& Player : PongPlayers)
		{
			AddScore(Player.Key, Gates->ArenaSide);
		}
	}
}
