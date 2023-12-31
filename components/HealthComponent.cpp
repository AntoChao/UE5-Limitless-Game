// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent(){
	
}

void UHealthComponent::SetHealth(float HP) {
	health = HP;
}

float UHealthComponent::GetHealth() {
	return health;
}

void UHealthComponent::InitHealth(float maxHP) {
	maxHealth = maxHP;
	SetHealth(maxHP);
}

float UHealthComponent::GetMaxHealth() {
	return maxHealth;
}

float UHealthComponent::GetHealthPercentage() {
	return health / maxHealth ;
}

// PercentageMod -> represent true damage (percentage damage) but also percentage healing
/* TYPES OF Health effect
float -> just a number
percentage of current health
percentage of maximum health
*/

void UHealthComponent::UpdateHealthFloat(float modifier) {
	float deltaHealth = health + modifier;

	// SOMETHING NOT WORKING OK

	// if player is died
	if (deltaHealth <= 0.0f) {
		health = 0.0f;
		SetDied(true);
	}
	// if the healing exceed -> is able to create more stuff
	else if (deltaHealth > maxHealth) {
		health = maxHealth;
		ExceedHealth = ExceedHealth + (deltaHealth - maxHealth);
	}
	else {
		health = health + modifier;
	}
}

// min -> -1, max -> +1
void UHealthComponent::UpdateHealthByPercentageOfCurrentHealth(float modifier) {
	float HealthToModify = health * modifier;
	// <0 -> means is damage
	if (modifier < 0.0f) {
		UpdateHealthFloat(-HealthToModify);
	}
	// >0 ->means is heal
	else if (modifier > 0.0f) {
		UpdateHealthFloat(HealthToModify);
	}
}

// min -> -1, max -> +1
void UHealthComponent::UpdateHealthByPercentageOfMaxHealth(float modifier) {
	float HealthToModify = maxHealth * modifier;
	// <0 -> means is damage
	if (modifier < 0.0f) {
		UpdateHealthFloat(-HealthToModify);
	}
	// >0 ->means is heal
	else if (modifier > 0.0f) {
		UpdateHealthFloat(HealthToModify);
	}
}

// Difference by health -> there never going to have a max health modifier that depend on current health
void UHealthComponent::UpdateMaxHealth(float modifier, float maxHealthMultiplier) {
	if (maxHealthMultiplier == 0) {
		if (maxHealth + modifier < MaxInt) {
			maxHealth += modifier;
		}
	}
	else {
		if (maxHealth * maxHealthMultiplier < MaxInt) {
			maxHealth = maxHealth * maxHealthMultiplier;
		}
	}
}

void UHealthComponent::RefillMaxHealth() {
	health = maxHealth;
}

void UHealthComponent::SetDied(bool HPState) {
	died = HPState;
}

bool UHealthComponent::GetDied() {
	return died;
}