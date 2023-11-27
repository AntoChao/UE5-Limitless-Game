// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageComponent.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UDamageComponent::UDamageComponent()
{

}

// Setter and Getter of basic values
void UDamageComponent::SetDamage(float damageValue)
{
	baseDamage = damageValue;
}

float UDamageComponent::GetDamage()
{
	return baseDamage;
}

void UDamageComponent::SetCritChance(float critChanceValue)
{
	critChance = critChanceValue;
}
float UDamageComponent::GetCritChance()
{
	return critChance;
}
void UDamageComponent::SetCritMultiplier(float critMultiplierValue)
{
	critMultiplier = critMultiplierValue;
}
float UDamageComponent::GetCritMultiplier()
{
	return critMultiplier;
}
void UDamageComponent::SetFireRate(float fireRateValue)
{
	fireRate = fireRateValue;
}
float UDamageComponent::GetFireRate()
{
	return fireRate;
}

float UDamageComponent::CalculateDamage(UCharacterPowerComponent* PowerComponent)
{
	float deltaBaseDamage = baseDamage + PowerComponent->GetPower();
	float deltaCritChance = critChance + PowerComponent->GetCharacCritChance();
	float deltaCritMultiplier = critMultiplier + PowerComponent->GetCharacCritMultiplier();

	if (CritictStrike(deltaCritChance))
	{
		return deltaBaseDamage * deltaCritMultiplier;
	}
	else
	{
		return deltaBaseDamage;
	}
}

bool UDamageComponent::CritictStrike(float Probability)
{
	float Chance = FMath::RandRange(1, 100);

	if (Chance <= Probability)
	{
		return true;
	}
	else
	{
		return false;
	}
}