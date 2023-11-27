// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterPowerComponent.h"

// Sets default values for this component's properties
UCharacterPowerComponent::UCharacterPowerComponent()
{

}

// Setter and Getter of basic values
void UCharacterPowerComponent::SetPower(float PowerValue)
{
	characBasePower = PowerValue;
}
float UCharacterPowerComponent::GetPower()
{
	return characBasePower;
}
void UCharacterPowerComponent::SetCharacCritChance(float critChanceValue)
{
	characBaseCritChance = critChanceValue;
}
float UCharacterPowerComponent::GetCharacCritChance()
{
	return characBaseCritChance;
}
void UCharacterPowerComponent::SetCharacCritMultiplier(float critMultiplierValue)
{
	characBaseCritMultipier = critMultiplierValue;
}
float UCharacterPowerComponent::GetCharacCritMultiplier()
{
	return characBaseCritMultipier;
}
void UCharacterPowerComponent::SetCharacAttackRate(float attackRateValue)
{
	characAttackRate = attackRateValue;
}
float UCharacterPowerComponent::GetCharacAttackRate()
{
	return characAttackRate;
}

// Updates Values
void UCharacterPowerComponent::UpdateFlatPower(float modifier)
{
	characBasePower = characBasePower + modifier;
}
// this percentage -> min = -1, max = 1
void UCharacterPowerComponent::UpdatePercentagePower(float modifier)
{
	float PowerPercentage = characBasePower * modifier;
	UpdateFlatPower(characBasePower);
}
void UCharacterPowerComponent::UpdateCritChance(float modifier)
{
	characBaseCritChance = characBaseCritChance + characBaseCritChance * modifier;
}
void UCharacterPowerComponent::UpdateCritMultiplier(float modifier)
{
	characBaseCritMultipier = characBaseCritMultipier + characBaseCritMultipier * modifier;
}
void UCharacterPowerComponent::UpdateAttackRate(float modifier)
{
	characAttackRate = characAttackRate + characAttackRate * modifier;
}