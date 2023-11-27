// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeneralAttackArtifact.h"
#include "Artifact_5_Punch.generated.h"

UCLASS()
class TRUEPROJECT2_API AArtifact_5_Punch : public AGeneralAttackArtifact
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AArtifact_5_Punch();

	float ratio = 2.0f;
	float distanceLimit = 50.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	virtual float ApplyAttackEffect(float deltaDamage, FHitResult EnemyHit, AMain* PlayerMain) override;

	void UpdateRatio(float newRatio);

};
