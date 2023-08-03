// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/PongPlayerController.h"
#include "Kismet/KismetMathLibrary.h"
//#include "Player/PongArenaCamera.h"

APongPlayerController::APongPlayerController()
	:
	PlatformVelocity(20.f),
	MinRange(-850.f),
	MaxRange(850.f)
{
	AutoManageActiveCameraTarget(false);
}

void APongPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveRight", this, &APongPlayerController::MovePlatform);
}

void APongPlayerController::MovePlatform(float Value)
{
	if (Value != 0)
	{
		float DeltaY = Value * PlatformVelocity;
		float NewDeltaLocation = DeltaY + DeltaLocation;

		if (UKismetMathLibrary::InRange_FloatFloat(NewDeltaLocation, MinRange, MaxRange))
		{
			DeltaLocation = NewDeltaLocation;
			AddPlatformOffSet(DeltaY);
		}
	}
}

/*void APongPlayerController::SetupPlayerCamera(APongArenaCamera* PongArenaCamera)
{
	SetViewTargetWithBlend(PongArenaCamera);
}*/

void APongPlayerController::AddPlatformOffSet_Implementation(float deltaY)
{
	GetPawn()->AddActorWorldOffset(FVector(0.f, deltaY, 0.f));
}

void APongPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (ArenaSide == RightSide)//TODO: Need to be assigned by gamemode
	{
		//PlatformVelocity = ;
	}
}
