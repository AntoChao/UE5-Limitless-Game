// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeneralDiedArtifact.h"
#include "Artifact_30_Heart.generated.h"

UCLASS()
class LIMITLESS_API AArtifact_30_Heart: public AGeneralDiedArtifact
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AArtifact_30_Heart();

	// linear scaling
	float revivePercentageHealth = 0.2;

public:	
	virtual bool ApplyDiedEffect(AMain* PlayerMain) override;

};
