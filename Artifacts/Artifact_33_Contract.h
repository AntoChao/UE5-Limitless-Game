// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeneralPickUpArtifact.h"
#include "Artifact_33_Contract.generated.h"

UCLASS()
class TRUEPROJECT2_API AArtifact_33_Contract : public AGeneralPickUpArtifact
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AArtifact_33_Contract();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	float ratio = 2.0f;

public:	
	virtual void ApplyPickUpEffect(AMain* MainCharacter) override;
	virtual void EliminatePickUpEffect(AMain* MainCharacter) override;
	
	void UpdateRatio(float newRatio);
};
