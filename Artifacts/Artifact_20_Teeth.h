// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeneralKillFeedBackArtifact.h"
#include "Artifact_20_Teeth.generated.h"

UCLASS()
class TRUEPROJECT2_API AArtifact_20_Teeth: public AGeneralKillFeedBackArtifact
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AArtifact_20_Teeth();

	// linear scaling
	float frenzyRatio  = 1.5f;
	float calmRatio = 1.5f;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	virtual UData_KillFeedBackInfo* ApplyKillFeedBackEffect(class UData_KillFeedBackInfo* KillInfo, AActor* Enemy) override;

	void UpdateFrenzyRatio(float newRatio);
	void UpdateCalmRatio(float newRatio);

};
