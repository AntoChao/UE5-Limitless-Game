// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeneralArtifact.h"
#include "GeneralKillFeedBackArtifact.generated.h"

UCLASS()
class TRUEPROJECT2_API AGeneralKillFeedBackArtifact : public AGeneralArtifact
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGeneralKillFeedBackArtifact();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UFUNCTION()
		virtual UData_KillFeedBackInfo* ApplyKillFeedBackEffect(class UData_KillFeedBackInfo* KillInfo, AActor* Enemy);
};
