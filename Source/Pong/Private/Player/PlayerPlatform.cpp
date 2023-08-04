// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerPlatform.h"

APlayerPlatform::APlayerPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlatformMesh"));
	PlatformMesh->SetRelativeScale3D(FVector(0.5f, 5.f, 2.5f));

	EAutoPossessAI::Disabled;

	bReplicates = true;
	PlatformMesh->SetIsReplicated(true);
}

void APlayerPlatform::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlayerPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerPlatform::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

