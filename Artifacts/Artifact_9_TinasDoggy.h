// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeneralPickUpArtifact.h"
#include "Artifact_9_TinasDoggy.generated.h"

UCLASS()
class LIMITLESS_API AArtifact_9_TinasDoggy: public AGeneralPickUpArtifact
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AArtifact_9_TinasDoggy();

	// linear scaling
	float ratio  = 0.15f;
	
public:	
	virtual void ApplyPickUpEffect(AMain* MainCharacter) override;
	virtual void EliminatePickUpEffect(AMain* MainCharacter) override;
	void UpdateRatio(float newRatio);

};
