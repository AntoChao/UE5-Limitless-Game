// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeneralArtifact.h"
#include "GeneralCostArtifact.generated.h"

UCLASS()
class TRUEPROJECT2_API AGeneralCostArtifact: public AGeneralArtifact
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGeneralCostArtifact();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UFUNCTION()
		virtual float ApplyFrenzyCostEffect(float FrenzyCost, AMain* MainCharacter);

	UFUNCTION()
		virtual float ApplyCalmCostEffect(float CalmCost, AMain* MainCharacter);

};
