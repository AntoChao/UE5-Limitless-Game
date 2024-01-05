// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeneralAbilityClass.h"
#include "Ability_Paralyze.generated.h"

/*
This ability is just to spawm a black hole bomb with corresponding functionality
*/

UCLASS()
class LIMITLESS_API AAbility_Paralyze : public AGeneralAbilityClass
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAbility_Paralyze(const class FObjectInitializer& ObjectInitializer);

protected:
	// Basic stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Stats")
		float ConeLength = 10000.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Stats")
		float ConeHalfAngle = 45.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Stats")
		float ParalyzeTime = 5.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Stats")
		TArray<AActor*> ActorsInRange = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Stats")
		TArray<AEnemyClass*> EnemiesParalyzed = {};

	// Reset Timer
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Stats")
		FTimerHandle ParalyzeTimer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Stats")
		float ParalyzeDuration = 5.0f;

	// Ability Paralyze effect
	void ParalyzeAllActorInCone(UData_AbilityRequiredInfo* requiredInfo);
	bool EnemyInRange(UData_AbilityRequiredInfo* requiredInfo, AActor* Enemy);

public:	
	virtual void ActivateAbilityEffect(UData_AbilityRequiredInfo* requiredInfo) override;
};
