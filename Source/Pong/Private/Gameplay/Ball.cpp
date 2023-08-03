// Fill out your copyright notice in the Description page of Project Settings.

#include "Gameplay/Ball.h"
#include "Kismet/KismetMathLibrary.h"
#include "Common/WallsInterface.h"
#include "Common/Walls.h"
#include "Player/PlayerPlatform.h"

ABall::ABall()
	:
	BallVelocity(1000)
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

}

void ABall::BeginPlay()
{
	Super::BeginPlay();
	
	bool RandomDirection = UKismetMathLibrary::RandomBool();
	float RandomX = UKismetMathLibrary::SelectFloat(1, -1, RandomDirection);

	RandomDirection = UKismetMathLibrary::RandomBool();
	float RandomY = UKismetMathLibrary::SelectFloat(1, -1, RandomDirection);

	Direction = FVector(RandomX, RandomY, 0.f);
}

void ABall::BallOffset(float deltatime)
{
	AddActorWorldOffset((BallVelocity * deltatime) * Direction);
}

void ABall::ChangeDirectionBasedOnWallType(AActor* TouchedWall)
{
	EWallType WallType;
	if (TouchedWall->GetClass()->ImplementsInterface(UWallsInterface::StaticClass()))
	{
		if (IWallsInterface* Interface = Cast<IWallsInterface>(TouchedWall))
		{
			WallType = Interface->GetWallType();

			switch (WallType)
			{
			case Side:
				ChangeSide();
				break;
			case Front:
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
	Direction = FVector((Direction.X*-1.f), Direction.Y, Direction.Z);
}

void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	BallOffset(DeltaTime);
}

void ABall::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ChangeDirectionBasedOnWallType(OtherActor);
}

