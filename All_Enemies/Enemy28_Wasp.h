// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyClass.h"
#include "Enemy28_Wasp.generated.h"

UCLASS()
class TRUEPROJECT2_API AEnemy28_Wasp : public AEnemyClass
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemy28_Wasp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Basic Stats
	
	// Maybe it has no attack ni abilities, it just follow the main and deal damage

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void CustomTickFunction() override;

	virtual void BasicAttack() override;
	virtual void Ability1() override;
};
