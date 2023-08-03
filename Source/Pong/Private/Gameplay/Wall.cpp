// Fill out your copyright notice in the Description page of Project Settings.

#include "Gameplay/Wall.h"

// Sets default values
AWall::AWall()
	:
	SideWallSize(41.f, 1.f, 3.f),
	FrontWallSize(6.f, 1.f, 3.f)
{
	PrimaryActorTick.bCanEverTick = true;

	WallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WallMesh"));
	WallMesh->SetupAttachment(GetRootComponent());
	WallMesh->SetGenerateOverlapEvents(true);
	WallMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
}

void AWall::BeginPlay()
{
	Super::BeginPlay();
}

EWallType AWall::GetWallType()
{
	return EWallType(WallType);
}

void AWall::ChangeSize()
{
	switch (WallType)
	{
	case Side:
		WallMesh->SetRelativeScale3D(SideWallSize);
		break;
	case Front:
		WallMesh->SetRelativeScale3D(FrontWallSize);
		break;
	default:
		break;
	}
}

void AWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}