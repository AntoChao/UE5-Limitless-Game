// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeneralAttackArtifact.h"
#include "Artifact_37_Drugs.generated.h"

UCLASS()
class LIMITLESS_API AArtifact_37_Drugs : public AGeneralAttackArtifact {
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AArtifact_37_Drugs();

	float ratio = 2.0f;

public:	
		virtual float ApplyAttackEffect(float deltaDamage, FHitResult EnemyHit, AMain* PlayerMain) override;

		void UpdateRatio(float newRatio);

};
