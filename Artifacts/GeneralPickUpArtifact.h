// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeneralArtifact.h"
#include "GeneralPickUpArtifact.generated.h"

UCLASS()
class TRUEPROJECT2_API AGeneralPickUpArtifact : public AGeneralArtifact
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGeneralPickUpArtifact();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()	
		virtual void ApplyPickUpEffect(AMain* MainCharacter);
	UFUNCTION()
		virtual void EliminatePickUpEffect(AMain* MainCharacter);
};
