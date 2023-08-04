// Fill out your copyright notice in the Description page of Project Settings.

#include "Gameplay/Wall.h"

AWall::AWall()
{
	PrimaryActorTick.bCanEverTick = false;

	WallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WallMesh"));
	WallMesh->SetupAttachment(GetRootComponent());
	WallMesh->SetGenerateOverlapEvents(true);
	WallMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
}