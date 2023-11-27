// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TrueGame2Instance.h"
#include "GameModeTest.generated.h"

UCLASS()
class TRUEPROJECT2_API AGameModeTest : public AGameModeBase
{
	GENERATED_BODY()

protected:
	
	// Player To Recognize
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main")
		TSubclassOf<class AMain> MainClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main")
		class AMain* MainCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main")
		bool MainIsSpawned = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main")
		FVector PlayerLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main")
		FRotator PlayerRotation;

public:
	AGameModeTest();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
