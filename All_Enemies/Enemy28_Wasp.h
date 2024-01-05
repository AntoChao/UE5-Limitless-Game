// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyClass.h"
#include "Enemy28_Wasp.generated.h"

UCLASS()
class LIMITLESS_API AEnemy28_Wasp : public AEnemyClass
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemy28_Wasp();

protected:
	// Maybe it has no attack ni abilities, it just follow the main and deal damage

public:
	// Called every frame
	virtual void CustomTickFunction() override;
};
