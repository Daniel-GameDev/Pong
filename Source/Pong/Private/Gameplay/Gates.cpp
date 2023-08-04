// Fill out your copyright notice in the Description page of Project Settings.

#include "Gameplay/Gates.h"
#include "Components/BoxComponent.h"

AGates::AGates()
{
	PrimaryActorTick.bCanEverTick = true;

	FVector DefaultSize = FVector(200.f, 600.f, 150.f);

	GatesCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("GatesCollision"));
	GatesCollision->SetupAttachment(GetRootComponent());
	GatesCollision->SetBoxExtent(DefaultSize);

	GatesCollision->OnComponentBeginOverlap.AddDynamic(this, &AGates::OnOverlapBegin);
}

void AGates::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OtherActor->Destroy();
}

