// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeneralPickUpArtifact.h"
#include "Artifact_34_Caffeine.generated.h"

UCLASS()
class TRUEPROJECT2_API AArtifact_34_Caffeine : public AGeneralPickUpArtifact
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AArtifact_34_Caffeine();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
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
