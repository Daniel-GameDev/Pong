// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/PlayerPlatform.h"
#include "Framework/PongGameMode.h"

APongGameMode::APongGameMode()
{
	DefaultPawnClass = APlayerPlatform::StaticClass();
}
