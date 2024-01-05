// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeneralDefenseArtifact.h"
#include "Artifact_27_Instinct.generated.h"

UCLASS()
class LIMITLESS_API AArtifact_27_Instinct: public AGeneralDefenseArtifact
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AArtifact_27_Instinct();

	// an max value
	float MaxRatioBoost = 10.0f;
	float ratioToSpeed = 3.0f;

public:	
	virtual float ApplyDefenseEffect(float deltaDamage, AMain* PlayerMain) override;
	void UpdateRatio(float newRatio);

};
