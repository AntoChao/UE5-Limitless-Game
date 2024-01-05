// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeneralAttackArtifact.h"
#include "Artifact_24_Coin.generated.h"

// lower the health == higher the damage
UCLASS()
class LIMITLESS_API AArtifact_24_Coin: public AGeneralAttackArtifact
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AArtifact_24_Coin();

	float generateFrenzyProb = 5.0f;
	float generateCalmProb = 5.0f;
	
	float ratio = 5.0f;

public:	
	virtual float ApplyAttackEffect(float deltaDamage, FHitResult EnemyHit, AMain* PlayerMain) override;

	void UpdateRatio(float newMax);

};
