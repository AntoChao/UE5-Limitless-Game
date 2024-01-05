// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeneralAbilityClass.h"
#include "Ability_FForward.generated.h"

UCLASS()
class LIMITLESS_API AAbility_FForward : public AGeneralAbilityClass
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAbility_FForward(const class FObjectInitializer& ObjectInitializer);

protected:

	UWorld* CurrentWorld;
	AMain* MainPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
		float FFowardDuration = 5.0f;

	// specific stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
		float NormalTimeDilation = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
		float TimeDilationMultiplier = 1.5f;

public:	
	virtual void ActivateAbilityEffect(UData_AbilityRequiredInfo* requiredInfo) override;
};
