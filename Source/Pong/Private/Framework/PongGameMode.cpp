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

AActor* APongGameMode::GetStartPoint(APongPlayerController* PongPlayer)
{
	if (PongPlayers.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player I Entered the Game as RightPlayer!"));

		PongPlayers.Add(PongPlayer, SetupPlayerData(RightSide));

		PongPlayer->PlatformVelocity = PongPlayer->PlatformVelocity * -1;

		//PongPlayer->ArenaSide == RightSide; //TODO: Delete ArenaSide in PlayerController?

		CreateWaitWidget(PongPlayer);

		return GetPlayerStart(RightSide);
	}
	else if (PongPlayers.Num() == 1)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player II Entered the Game as LeftPlayer!"));

		PongPlayers.Add(PongPlayer, SetupPlayerData(LeftSide));

		//PongPlayer->PlatformVelocity = PongPlayer->PlatformVelocity * -1;

		return GetPlayerStart(LeftSide);
	}

	return nullptr;
}

FPongPlayer APongGameMode::SetupPlayerData(ArenaSides arenaSide)
{
	TArray<AActor*> GatesArray;;
	TArray<AActor*> CameraArray;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGates::StaticClass(), GatesArray);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APongArenaCamera::StaticClass(), CameraArray);

	FPongPlayer PongPlayerTempStruct;
	PongPlayerTempStruct.ArenaSide = arenaSide;

	for (AActor* TGates : GatesArray)
	{
		AGates* Gate = Cast<AGates>(TGates);

		if (Gate != nullptr)
		{
			if ((Gate->ArenaSide) == arenaSide)
			{
				PongPlayerTempStruct.PlayerGates = Gate;
			}
		}
	}

	for (AActor* TPongCamera : CameraArray)
	{
		APongArenaCamera* PongCam = Cast<APongArenaCamera>(TPongCamera);

		if (PongCam != nullptr)
		{
			if ((PongCam->ArenaSide) == arenaSide)
			{
				PongPlayerTempStruct.PlayerArenaCamera = PongCam;
			}
		}
	}

	return PongPlayerTempStruct;
}
APongPlayerStart* APongGameMode::GetPlayerStart(ArenaSides arenaSide)
{
	APongPlayerStart* TempPlayerStart = nullptr;
	TArray<AActor*> GameStarArray;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APongPlayerStart::StaticClass(), GameStarArray);

	for (AActor* TStartPoint : GameStarArray)
	{
		APongPlayerStart* PlayerStart = Cast<APongPlayerStart>(TStartPoint);

		if (PlayerStart != nullptr)
		{
			if ((PlayerStart->ArenaSide) == arenaSide)
			{
				TempPlayerStart = PlayerStart;
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

	if (GetWorld()->GetAuthGameMode()->GetNumPlayers() < 2)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Waiting for Second Player.."));
	}
	else if (GetWorld()->GetAuthGameMode()->GetNumPlayers() == 2)
	{
		SpawnBall();
	}
}
void APongGameMode::SpawnBall()
{
	FVector Location(0.f, 0.f, 200.f);
	FRotator Rotation(0.f, 0.f, 0.f);

	UObject* SpawnActor = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, TEXT("/Game/Pong/Blueprints/Gameplay/Converted/BP_Ball_C")));
	UBlueprint* GeneratedBP = Cast<UBlueprint>(SpawnActor);
	if (!SpawnActor)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("CANT FIND OBJECT TO SPAWN")));
		return;
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	GetWorld()->SpawnActor<ABall>(GeneratedBP->GeneratedClass, Location, Rotation, SpawnParams);
}
void APongGameMode::OnComponentEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AGates* Gates = Cast<AGates>(OverlappedComp->GetOwner());

	if (Gates != nullptr)
	{
		switch (Gates->ArenaSide)
		{
		case RightSide:
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("RIGHT")));
			break;
		case LeftSide:
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("LEFT")));
			break;
		default:
			break;
		}

		FTimerHandle UnusedHandle;
		GetWorldTimerManager().SetTimer(UnusedHandle, this, &APongGameMode::SpawnBall, 2.f, false);
	}
}

void APongGameMode::CreateWaitWidget(APongPlayerController* PongPlayer)
{
	/*if (WaitWidget)
	{
		WaitWidgetInstance = CreateWidget<UUserWidget>(this, WaitWidget);

		if (WaitWidgetInstance)
		{
			WaitWidgetInstance->AddToViewport();
		}
	}*/

	/*ConstructorHelpers::FClassFinder<UUserWidget> WaitWidgetRef(TEXT("/Game/Blueprints/UI/WBP_Wait"));
	TSubclassOf<UUserWidget> WaitWidget;
	if (WaitWidgetRef.Class)
	{
		WaitWidget = WaitWidgetRef.Class;
	}*/
	

	/*UUserWidget* WaitWidget = Cast<UUserWidget>(StaticLoadObject(UObject::StaticClass(), NULL, TEXT("/Game/Blueprints/UI/WBP_Wait")));
	UBlueprint* GeneratedBP = Cast<UBlueprint>(WaitWidget);*/

	/*FStringClassReference WaitWidgetRef(TEXT("/Game/Blueprints/UI/WBP_Wait"));
	UClass* WaitWidget = WaitWidgetRef.TryLoadClass<UUserWidget>();
	UUserWidget* WaitWidgetInstance = Cast<UUserWidget>(WaitWidget);*/

	//UObject* SpawnActor = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, TEXT("/Game/Pong/Blueprints/Gameplay/Converted/BP_Ball_C")));
	//UBlueprint* GeneratedBP = Cast<UBlueprint>(SpawnActor);
	/*if (IsValid(WidgetClass))
	{
		FStringClassReference WaitWidgetRef(TEXT("/Game/Blueprints/UI/WBP_Wait"));
		UClass* WaitWidget = WaitWidgetRef.TryLoadClass<UUserWidget>();
		WaitWidget = Cast<UUserWidget>CreateWidget(GetWorld(), WidgetClass);
	}

	//static ConstructorHelpers::FClassFinder<UUserWidget> WaitWidget(TEXT("/Game/Blueprints/UI/WBP_Wait"));

	

	if (WaitWidget != nullptr)
	{
		UUserWidget* Wait = CreateWidget<UUserWidget>(this->GetGameInstance(), WaitWidget);
		//UUserWidget* Wait = CreateWidget<UUserWidget>(PongPlayer, WaitWidget);
		Wait->AddToViewport();
	}*/
	/*FStringClassReference WidgetWaitRef();
	UClass* WaitWidget = WidgetWaitRef.TryLoadClass<UUserWidget>();
	if (WaitWidget)
	{
		UUserWidget* WaitWidget = CreateWidget<UUserWidget>(this->GetGameInstance(), WaitWidget);
		if (WaitWidget)
		{
			WaitWidget->AddToViewport();
		}	
	}*/
}
