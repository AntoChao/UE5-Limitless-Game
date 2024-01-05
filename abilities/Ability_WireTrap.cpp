// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability_WireTrap.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Engine/EngineTypes.h"
#include "Engine/Blueprint.h"
#include "DrawDebugHelpers.h"
#include "Math/Vector.h"
#include "../Main.h"
#include "../meshes/Weapon_BlackHoleBomb.h"
#include "../AllCharactersClass.h"

// Sets default values
AAbility_WireTrap::AAbility_WireTrap(const class FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

/*  ActivateAbilityEffect has 3 process
*	Customize ability stats
*	Do the effect
*	Calculate feedback in order to return -> override all calculution base on ability
*/
void AAbility_WireTrap::ActivateAbilityEffect(UData_AbilityRequiredInfo* requiredInfo)
{
	// Ability Effect -> Spawn the grenade in hand and manipulate the character to throw and release
	SpawnBlackHoleBomb(requiredInfo);
	// run a tick TIMER to contanstly check the player decision, 
	// if she is going to accept or reject the ability use
	
	// Calculate the feedback -> override all calculation -> the calculation is done after receive the decision
	// freCost, freReward, cocost, coReward, moveSpeedRew, Xp
}
void AAbility_WireTrap::SpawnBlackHoleBomb(UData_AbilityRequiredInfo* requiredInfo)
{
	// The Attach should not be part of the ability, it is responsability of the main character
	requiredInfo->GetPlayer()->AttachWeaponSelected(requiredInfo->GetAbilityCode());
}