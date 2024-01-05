// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeneralPickUpArtifact.h"
#include "Artifact_32_Medkit.generated.h"

UCLASS()
class LIMITLESS_API AArtifact_32_Medkit : public AGeneralPickUpArtifact
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AArtifact_32_Medkit();

public:	
	virtual void ApplyPickUpEffect(AMain* MainCharacter) override;
	virtual void EliminatePickUpEffect(AMain* MainCharacter) override;
};
