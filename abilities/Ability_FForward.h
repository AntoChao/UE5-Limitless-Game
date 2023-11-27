// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeneralAbilityClass.h"
#include "Ability_FForward.generated.h"

UCLASS()
class TRUEPROJECT2_API AAbility_FForward : public AGeneralAbilityClass
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAbility_FForward(const class FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UWorld* CurrentWorld;
	AMain* MainPlayer;

	FTimerHandle FFowardTimer;
	float FFowardDuration = 5.0f;
	void ResetTimeDilation();

	// specific stats
	float NormalTimeDilation = 1.0f;
	float TimeDilationMultiplier = 1.5f;
	float CurrentTimeDilation = 1.0f;

public:	
	virtual bool AbilityRequirement(UData_AbilityRequiredInfo* requiredInfo) override;

	virtual void ActivateAbilityEffect(UData_AbilityRequiredInfo* requiredInfo) override;
};
