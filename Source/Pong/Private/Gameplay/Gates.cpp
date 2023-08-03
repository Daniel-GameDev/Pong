// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/BoxComponent.h"
#include "Gameplay/Gates.h"

AGates::AGates()
{
	PrimaryActorTick.bCanEverTick = true;

	GatesCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("GatesCollision"));
	GatesCollision->SetupAttachment(GetRootComponent());
	GatesCollision->SetBoxExtent(FVector(200.f, 600.f, 150.f));

	GatesCollision->OnComponentBeginOverlap.AddDynamic(this, &AGates::OnOverlapBegin);
}

void AGates::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OtherActor->Destroy();
}

void AGates::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGates::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

