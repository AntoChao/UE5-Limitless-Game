// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeneralPickUpArtifact.h"
#include "Artifact_40_Fugu.generated.h"

UCLASS()
class LIMITLESS_API AArtifact_40_Fugu : public AGeneralPickUpArtifact
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AArtifact_40_Fugu();

protected:
	float ratio = 2.0f;

	AMain* MainPlayer = nullptr;

	bool ShouldBeEliminateEffect = false;
	FTimerHandle EliminateEffectTimer;
	float EffectDuration = 10.0f;

public:	
	virtual void ApplyPickUpEffect(AMain* MainCharacter) override;
	virtual void EliminatePickUpEffect(AMain* MainCharacter) override;
	void EliminatePickUpEffectByTime();
};
