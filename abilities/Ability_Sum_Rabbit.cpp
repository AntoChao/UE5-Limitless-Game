// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability_Sum_Rabbit.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Engine/EngineTypes.h"
#include "Engine/Blueprint.h"
#include "DrawDebugHelpers.h"
#include "Math/Vector.h"
#include "../All_Enemies/Enemy31_KillerRabbit.h"
#include "../AllCharactersClass.h"

// Sets default values
AAbility_Sum_Rabbit::AAbility_Sum_Rabbit(const class FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{

}

/*  ActivateAbilityEffect has 3 process
*	Customize ability stats
*	Do the effect
*	Calculate feedback in order to return -> override all calculution base on ability
*/
void AAbility_Sum_Rabbit::ActivateAbilityEffect(UData_AbilityRequiredInfo* requiredInfo)
{
	// Ability Effect -> Spawn the grenade in hand and manipulate the character to throw and release
	SpawnRabbit(requiredInfo);

	// Calculate the feedback -> override all calculation -> the calculation is done after receive the decision
	// freCost, freReward, cocost, coReward, moveSpeedRew, Xp
}

// just spawn a rabbit which has its own logic. player can not influence it at all
void AAbility_Sum_Rabbit::SpawnRabbit(UData_AbilityRequiredInfo* requiredInfo)
{
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FVector SpawnLocation = requiredInfo->GetPlayer()->GetForwardDirection() * 50.0f +requiredInfo->GetPlayerLocation();

	// the rotation could be random
	requiredInfo->GetWorldPointer()->SpawnActor<AEnemy31_KillerRabbit>(
		Enemy31_KillerRabbitClass, SpawnLocation,
		requiredInfo->GetPlayer()->GetActorRotation(), ActorSpawnParams);

	// Player should not have any control about it, because it has its own logic 
}