// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeneralDefenseArtifact.h"
#include "Artifact_17_Cloak.generated.h"

UCLASS()
class LIMITLESS_API AArtifact_17_Cloak: public AGeneralDefenseArtifact
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AArtifact_17_Cloak();

	// linear scaling
	float ratio  = 1.25f;
	
public:	
	virtual float ApplyDefenseEffect(float deltaDamage, AMain* PlayerMain) override;
	void UpdateRatio(float newRatio);

};
