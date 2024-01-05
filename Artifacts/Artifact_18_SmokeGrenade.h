// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeneralDefenseArtifact.h"
#include "Artifact_18_SmokeGrenade.generated.h"

UCLASS()
class LIMITLESS_API AArtifact_18_SmokeGrenade: public AGeneralDefenseArtifact
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AArtifact_18_SmokeGrenade();

	// linear scaling
	float dodgeRatio  = 10.0f;
	
public:	
	virtual float ApplyDefenseEffect(float deltaDamage, AMain* PlayerMain) override;
	void UpdateRatio(float newRatio);

};
