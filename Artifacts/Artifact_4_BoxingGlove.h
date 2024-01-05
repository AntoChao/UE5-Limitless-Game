// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeneralAttackArtifact.h"
#include "Artifact_4_BoxingGlove.generated.h"

UCLASS()
class LIMITLESS_API AArtifact_4_BoxingGlove : public AGeneralAttackArtifact
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AArtifact_4_BoxingGlove();

	float ratio = 1.7f;

public:	
	virtual float ApplyAttackEffect(float deltaDamage, FHitResult EnemyHit, AMain* PlayerMain) override;

	void UpdateRatio(float newRatio);

};
