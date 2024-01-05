// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeneralPickUpArtifact.h"
#include "Artifact_38_Totem.generated.h"

UCLASS()
class LIMITLESS_API AArtifact_38_Totem : public AGeneralPickUpArtifact
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AArtifact_38_Totem();

protected:
	float ratio = 0.2;

public:	
	virtual void ApplyPickUpEffect(AMain* MainCharacter) override;
	virtual void EliminatePickUpEffect(AMain* MainCharacter) override;
};
