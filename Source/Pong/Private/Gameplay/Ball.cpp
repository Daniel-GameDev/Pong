// Fill out your copyright notice in the Description page of Project Settings.

#include "Gameplay/Ball.h"
#include "Kismet/KismetMathLibrary.h"
#include "Common/WallsInterface.h"
#include "Common/Walls.h"
#include "Player/PlayerPlatform.h"

ABall::ABall()
	:
	Velocity(1000)
{
	PrimaryActorTick.bCanEverTick = true;

	BallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BallMesh"));
	BallMesh->SetupAttachment(GetRootComponent());

	BallMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	BallMesh->SetGenerateOverlapEvents(true);

	BallMesh->BodyInstance.bLockXRotation = true;
	BallMesh->BodyInstance.bLockYRotation = true;
	BallMesh->BodyInstance.bLockZTranslation = true;

	BallMesh->OnComponentBeginOverlap.AddDynamic(this, &ABall::OnOverlapBegin);

	bReplicates = true;
	BallMesh->SetIsReplicated(true);
}

void ABall::BeginPlay()
{
	Super::BeginPlay();
	
	SetRandomDirection();
}

void ABall::Offset(float deltatime)
{
	AddActorWorldOffset((Velocity * deltatime) * Direction);
}

void ABall::ChangeDirectionByWallType(AActor* TouchedWall)
{
	if (TouchedWall->GetClass()->ImplementsInterface(UWallsInterface::StaticClass()))
	{
		if (IWallsInterface* Interface = Cast<IWallsInterface>(TouchedWall))
		{
			switch (Interface->GetWallType())
			{
			case EWT_Side:
				ChangeSide();
				break;
			case EWT_Front:
				ChangeDirection();
				break;
			default:
				break;
			}
		}
	}else if (Cast<APlayerPlatform>(TouchedWall))
	{
		ChangeDirection();
	}
}

void ABall::ChangeSide()
{
	Direction = FVector(Direction.X, (Direction.Y * -1.f), Direction.Z);
}

void ABall::ChangeDirection()
{
	Direction = FVector((Direction.X * -1.f), Direction.Y, Direction.Z);
}

void ABall::SetRandomDirection()
{
	bool RandomDirection = UKismetMathLibrary::RandomBool();
	float RandomX = UKismetMathLibrary::SelectFloat(1, -1, RandomDirection);

	RandomDirection = UKismetMathLibrary::RandomBool();
	float RandomY = UKismetMathLibrary::SelectFloat(1, -1, RandomDirection);

	Direction = FVector(RandomX, RandomY, 0.f);
}

void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Offset(DeltaTime);
}

void ABall::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ChangeDirectionByWallType(OtherActor);
}

