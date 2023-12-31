// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeneralPickUpArtifact.h"
#include "Artifact_14_Horseshoe.generated.h"

UCLASS()
class LIMITLESS_API AArtifact_14_Horseshoe: public AGeneralPickUpArtifact
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AArtifact_14_Horseshoe();

	// linear scaling
	float ratio  = 1.25f;
	
public:	
	virtual void ApplyPickUpEffect(AMain* MainCharacter) override;
	virtual void EliminatePickUpEffect(AMain* MainCharacter) override;
	void UpdateRatio(float newRatio);

};
