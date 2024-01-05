// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeneralArtifact.h"
#include "GeneralDefenseArtifact.generated.h"

UCLASS()
class LIMITLESS_API AGeneralDefenseArtifact : public AGeneralArtifact
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGeneralDefenseArtifact();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UFUNCTION()
		virtual float ApplyDefenseEffect(float deltaDamage, AMain* PlayerMain);
};
