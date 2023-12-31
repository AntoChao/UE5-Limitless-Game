// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeneralPickUpArtifact.h"
#include "Artifact_22_Headphone.generated.h"

UCLASS()
class LIMITLESS_API AArtifact_22_Headphone : public AGeneralPickUpArtifact
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AArtifact_22_Headphone();

	float ratio = 1.2f;

public:	
	virtual void ApplyPickUpEffect(AMain* MainCharacter) override;
	virtual void EliminatePickUpEffect(AMain* MainCharacter) override;
	void UpdateRatio(float newRatio);

};
