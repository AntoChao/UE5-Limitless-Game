// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeneralAttackArtifact.h"
#include "Artifact_6_SniperRifle.generated.h"

UCLASS()
class LIMITLESS_API AArtifact_6_SniperRifle: public AGeneralAttackArtifact
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AArtifact_6_SniperRifle();

	float ratio = 2.0f;
	float distanceLimit = 100.0f;

public:	
	virtual float ApplyAttackEffect(float deltaDamage, FHitResult EnemyHit, AMain* PlayerMain) override;

	void UpdateRatio(float newRatio);

};
