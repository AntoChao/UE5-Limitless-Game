// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability_Open_Command.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Engine/EngineTypes.h"
#include "Engine/Blueprint.h"
#include "DrawDebugHelpers.h"
#include "Math/Vector.h"
#include "../meshes/Weapon_MomFoot.h"
#include "../AllCharactersClass.h"

// Sets default values
AAbility_Open_Command::AAbility_Open_Command(const class FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer){
}

/*  ActivateAbilityEffect has 3 process
*	Customize ability stats
*	Do the effect
*	Calculate feedback in order to return -> override all calculution base on ability
*/
void AAbility_Open_Command::ActivateAbilityEffect(UData_AbilityRequiredInfo* requiredInfo)
{
	// Ability Effect
	requiredInfo->GetPlayer()->SetCurrentAbilityInHand(EAbilityCode::EOpenCommand);

	// Calculate the feedback -> override all calculation -> the calculation is done after receive the decision
	// freCost, freReward, cocost, coReward, moveSpeedRew, Xp
}

// QUESTION -> ABILITY COST -> Possibilities: BY LETTER/ time...

/*Ability Effect 
* 1: Player get in command HUD -> disable movement
* 2: Player only exit when they press enter or esc.
* 3: all others keys are just like typing.
* 4: while the ability is running -> each type is recorded and displayed in command
* 5: when press enter -> cut the recording and validate the input
* 6: if the input match some really meaningful command -> then run the command
*/
