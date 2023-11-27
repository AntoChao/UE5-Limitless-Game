// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeneralAttackArtifact.h"
#include "Artifact_12_pumpkin.generated.h"

// lower the health == higher the damage
UCLASS()
class TRUEPROJECT2_API AArtifact_12_pumpkin: public AGeneralAttackArtifact
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AArtifact_12_pumpkin();

	float MaxBoost = 10.0f;
	float ratioToScale = 5.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	virtual float ApplyAttackEffect(float deltaDamage, FHitResult EnemyHit, AMain* PlayerMain) override;

	void UpdateRatio(float newMax);

};
