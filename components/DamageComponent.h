// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterPowerComponent.h"
#include "DamageComponent.generated.h"

/* Damage Component
* Every actor that is able to deal damage should have a damage component
* Which contain information such as: base dmg, crit prob...
* Is able to receive character stats -> update new values...
* Character should not have this component, as they do not deal damage directly
*/ 
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRUEPROJECT2_API UDamageComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDamageComponent();

protected:
	// Basic Stats
	float baseDamage = 0.0f;
	float critChance = 0.0f;
	float critMultiplier = 0.0f;
	float fireRate = 0.0f;

public:	
	// Getters and Setters
	void SetDamage(float damageValue);
	float GetDamage();
	void SetCritChance(float critChanceValue);
	float GetCritChance();
	void SetCritMultiplier(float critMultiplierValue);
	float GetCritMultiplier();
	void SetFireRate(float fireRateValue);
	float GetFireRate();

	// Futher functionalities
	float CalculateDamage(UCharacterPowerComponent* PowerComponent);
	bool CritictStrike(float Probability);

};
