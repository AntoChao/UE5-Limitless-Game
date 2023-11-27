// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeneralPickUpArtifact.h"
#include "Artifact_36_Cigaratte.generated.h"

UCLASS()
class TRUEPROJECT2_API AArtifact_36_Cigaratte : public AGeneralPickUpArtifact
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AArtifact_36_Cigaratte();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	float ratio = 0.2;

public:	
	virtual void ApplyPickUpEffect(AMain* MainCharacter) override;
	virtual void EliminatePickUpEffect(AMain* MainCharacter) override;
};
