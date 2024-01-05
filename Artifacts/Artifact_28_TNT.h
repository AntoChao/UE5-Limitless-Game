// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeneralKillFeedBackArtifact.h"
#include "Artifact_28_TNT.generated.h"

UCLASS()
class LIMITLESS_API AArtifact_28_TNT: public AGeneralKillFeedBackArtifact
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AArtifact_28_TNT();

	// linear scaling
	float radius = 50.0f;
	float ratioDamage = 10.0f;
	
	TArray<AActor*> ignoredActors;

public:	
	virtual UData_KillFeedBackInfo* ApplyKillFeedBackEffect(class UData_KillFeedBackInfo* KillInfo, AActor* Enemy) override;

};
