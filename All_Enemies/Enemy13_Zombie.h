// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyClass.h"
#include "Enemy13_Zombie.generated.h"

UCLASS()
class LIMITLESS_API AEnemy13_Zombie : public AEnemyClass
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemy13_Zombie();

protected:

	//Basic Stats

	UPROPERTY(EditAnywhere, Category = "Enemies")
		TSubclassOf<class AMain> MainClass;
};
