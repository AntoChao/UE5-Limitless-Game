// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeneralDefenseArtifact.h"
#include "Artifact_39_Whip.generated.h"

UCLASS()
class TRUEPROJECT2_API AArtifact_39_Whip : public AGeneralDefenseArtifact
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AArtifact_39_Whip();

	// an max value
	float MaxRatioBoost = 10.0f;
	float ratioToSpeed = 3.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	virtual float ApplyDefenseEffect(float deltaDamage, AMain* PlayerMain) override;
	void UpdateRatio(float newRatio);

};
