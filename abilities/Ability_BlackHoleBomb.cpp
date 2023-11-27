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
	:Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAbility_BlackHoleBomb::BeginPlay()
{
	Super::BeginPlay();
}

bool AAbility_BlackHoleBomb::AbilityRequirement(UData_AbilityRequiredInfo* requiredInfo)
{
	if (requiredInfo->GetPlayerFrenzy() >= FrenzyCost->GetFrenzy())
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("USING BlackHole Bomb"));
		return true;
	}
	else
	{
		return false;
	}
	
}

/*  ActivateAbilityEffect has 3 process
*	Customize ability stats
*	Do the effect
*	Calculate feedback in order to return -> override all calculution base on ability
*/
void AAbility_BlackHoleBomb::ActivateAbilityEffect(UData_AbilityRequiredInfo* requiredInfo)
{
	// Ability Effect -> Spawn the grenade in hand and manipulate the character to throw and release
	SpawnBlackHoleBomb(requiredInfo);

	// Calculate the feedback -> override all calculation -> the calculation is done after receive the decision
	// freCost, freReward, cocost, coReward, moveSpeedRew, Xp
}

void AAbility_BlackHoleBomb::SpawnBlackHoleBomb(UData_AbilityRequiredInfo* requiredInfo)
{
	// NO DO ANYTHING. ALL RESPONDED BY ABILITY SYSTEM AND MAIN
}