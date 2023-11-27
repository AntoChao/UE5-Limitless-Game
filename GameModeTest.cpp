// Copyright Epic Games, Inc. All Rights Reserved.


#include "GameModeTest.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"
#include "Math/Vector.h"
#include "NavigationSystem.h"
#include "TimerManager.h"

#include "Main.h"

// Enemies
#include "All_Enemies/EnemyClass.h"
#include "All_Enemies/BasicEnemy.h"

AGameModeTest::AGameModeTest()
{
    PrimaryActorTick.bCanEverTick = true;

    DefaultPawnClass = AMain::StaticClass();
}

void AGameModeTest::BeginPlay()
{
    Super::BeginPlay();

    // Just Try to Spawn the main Character and possess it

    // ***** Need to add logic about where spawn player and not just restart it
    FActorSpawnParameters ActorSpawnParams;
    ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    //MainHalfHeight = MainCharacter->GetMainHalfHeight();
    float MainHalfHeight = 200.0f;
    FVector PlaceToSpawnMain = FVector(100.0f, 100.0f, 4000.0f) + FVector(0.0f, 0.0f, MainHalfHeight);

    MainCharacter = GetWorld()->SpawnActor<AMain>(MainClass, PlaceToSpawnMain, FRotator(0.0f, 0.0f, 0.0f), ActorSpawnParams);

	// Controller the main by possession

	// Just testing if the cast is valid -> should migrate the controller logic to controller
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (MainCharacter)
	{
		if (PlayerController)
		{
			// PlayerController->Possess(MainCharacter);
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, TEXT("Player controller is valid"));
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, TEXT("Player controller is NOT valid"));
		}

		AMainController* MainController = Cast<AMainController>(PlayerController);
		if (MainController)
		{
			MainController->Possess(MainCharacter);
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, TEXT("Main Controller is valid"));
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, TEXT("Main Controller is NOT valid"));
		}
	}
	
}

// Called every frame
void AGameModeTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);    

}