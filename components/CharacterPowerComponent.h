// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterPowerComponent.generated.h"

/* Damage Component
* Every actor that is able to deal damage should have a damage component
* Which contain information such as: base dmg, crit prob...
* Is able to receive character stats -> update new values...
* Character should not have this component, as they do not deal damage directly
*/ 
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRUEPROJECT2_API UCharacterPowerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCharacterPowerComponent();

protected:
	// Basic Stats
	float characBasePower = 0.0f;
	float characBaseCritChance = 0.0f;
	float characBaseCritMultipier = 0.0f;
	float characAttackRate = 1.0f;

public:	
	// Setters and Getters
	void SetPower(float PowerValue);
	float GetPower();
	void SetCharacCritChance(float critChanceValue);
	float GetCharacCritChance();
	void SetCharacCritMultiplier(float critMultiplierValue);
	float GetCharacCritMultiplier();
	void SetCharacAttackRate(float attackRateValue);
	float GetCharacAttackRate();

	// Updates Values
	void UpdateFlatPower(float modifier);
	void UpdatePercentagePower(float modifier);
	
	void UpdateCritChance(float modifier);
	void UpdateCritMultiplier(float modifier);
	void UpdateAttackRate(float modifier);
};
