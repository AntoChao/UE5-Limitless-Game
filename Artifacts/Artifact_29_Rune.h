// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeneralCostArtifact.h"
#include "Artifact_29_Rune.generated.h"

UCLASS()
class TRUEPROJECT2_API AArtifact_29_Rune : public AGeneralCostArtifact
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AArtifact_29_Rune();

	// linear scaling
	float ratio  = 1.0f;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	virtual float ApplyFrenzyCostEffect(float FrenzyCost, AMain* MainCharacter) override;
	virtual float ApplyCalmCostEffect(float CalmCost, AMain* MainCharacter) override;
};
