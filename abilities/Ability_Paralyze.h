// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeneralAbilityClass.h"
#include "Ability_Paralyze.generated.h"

/*
This ability is just to spawm a black hole bomb with corresponding functionality
*/

UCLASS()
class TRUEPROJECT2_API AAbility_Paralyze : public AGeneralAbilityClass
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAbility_Paralyze(const class FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Basic stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Stats")
		float ConeLength = 500.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Stats")
		float ConeHalfAngle = 45.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Stats")
		TArray<AActor*> ActorsInRange = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Stats")
		TArray<AActor*> ActorsParalyzed = {};

	FTimerHandle ParalyzeTimeTimer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Stats")
		float ParalyzeTimeDuration = 3.0f;
	void ResetParalyzeEffect();

	// Ability Requirement -> just frenzy and calm

	// Ability Paralyze effect
	void GetAllActorInCone(UData_AbilityRequiredInfo* requiredInfo);
	bool EnemyInRange(UData_AbilityRequiredInfo* requiredInfo, AActor* Enemy);

public:	
	virtual bool AbilityRequirement(UData_AbilityRequiredInfo* requiredInfo) override;
	virtual void ActivateAbilityEffect(UData_AbilityRequiredInfo* requiredInfo) override;
};
