// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeneralPickUpArtifact.h"
#include "Artifact_35_Wings.generated.h"

UCLASS()
class TRUEPROJECT2_API AArtifact_35_Wings : public AGeneralPickUpArtifact
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AArtifact_35_Wings();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	AMain* MainPlayer = nullptr;

	bool ShouldBeEliminateEffect = false;
	FTimerHandle EliminateEffectTimer;
	float EffectDuration = 10.0f;

public:	
	virtual void ApplyPickUpEffect(AMain* MainCharacter) override;
	virtual void EliminatePickUpEffect(AMain* MainCharacter) override;
	void EliminatePickUpEffectByTime();
};
