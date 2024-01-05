// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LIMITLESS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// base stats
	int MaxInt = 2147483647;
	float health = 0.0f;
	float maxHealth = 0.0f;
	bool died = false;

	// extra variables
	// Is able to use exceedhealth to do more things
	float ExceedHealth = 0.0f;

public:	
	// setters and getters
	void InitHealth(float HP);
	void SetHealth(float HP);
	float GetHealth();
	void SetMaxHealth(float maxHP);
	float GetMaxHealth();

	float GetHealthPercentage();
	void UpdateHealthFloat(float modifier);
	void UpdateHealthByPercentageOfCurrentHealth(float modifier);
	void UpdateHealthByPercentageOfMaxHealth(float modifier);

	void UpdateMaxHealth(float modifier, float maxHealthMultiplier);
	void RefillMaxHealth();

	void SetDied(bool HPState);
	bool GetDied();
};
