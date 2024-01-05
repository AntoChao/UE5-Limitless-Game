// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability_BlackHoleBomb.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Engine/EngineTypes.h"
#include "Engine/Blueprint.h"
#include "DrawDebugHelpers.h"
#include "Math/Vector.h"
#include "../meshes/Weapon_BlackHoleBomb.h"
#include "../AllCharactersClass.h"

// Sets default values
AAbility_BlackHoleBomb::AAbility_BlackHoleBomb(const class FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer) {

}

/*  ActivateAbilityEffect has 3 process
*	Customize ability stats
*	Do the effect
*	Calculate feedback in order to return -> override all calculution base on ability
*/
void AAbility_BlackHoleBomb::ActivateAbilityEffect(UData_AbilityRequiredInfo* requiredInfo) {
	SpawnBlackHoleBomb(requiredInfo);
}