// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability_Paralyze.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Engine/EngineTypes.h"
#include "Engine/Blueprint.h"
#include "DrawDebugHelpers.h"
#include "Math/Vector.h"
#include "../meshes/Weapon_BlackHoleBomb.h"
#include "../AllCharactersClass.h"

// Sets default values
AAbility_Paralyze::AAbility_Paralyze(const class FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAbility_Paralyze::BeginPlay()
{
	Super::BeginPlay();
}

bool AAbility_Paralyze::AbilityRequirement(UData_AbilityRequiredInfo* requiredInfo)
{
	if (requiredInfo->GetPlayerFrenzy() >= FrenzyCost->GetFrenzy())
	{
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
void AAbility_Paralyze::ActivateAbilityEffect(UData_AbilityRequiredInfo* requiredInfo)
{
	// Ability Effect -> Spawn the grenade in hand and manipulate the character to throw and release
	// should not have any more possibilities, other wise unable
	

	// Calculate the feedback -> override all calculation -> the calculation is done after receive the decision
	// freCost, freReward, cocost, coReward, moveSpeedRew, Xp
}


// I can use overlap to get all actors, but this is maybe better as it just run once
/* DECISION, FILTER -> APPLY EFFECT AFTERWARD OR APPLY DIRECTLY
1: Get All Actors in world
2: Filter all actors that are not enemies
3: Filter all actors that are not in sphere range
4: Filter all actors that are not in cone range
*/
void AAbility_Paralyze::GetAllActorInCone(UData_AbilityRequiredInfo* requiredInfo)
{
	ActorsInRange = {};
	// Find all actors in world
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), ActorsInRange);

	for (AActor* Actor : ActorsInRange)
	{
		// check if actor is enemy:
		if (Actor->GetClass()->IsChildOf(AEnemyClass::StaticClass()))
		{
			// check if the enemy "valid"
			if (IsValid(Actor))
			{
				// is in range
				if (EnemyInRange(requiredInfo, Actor))
				{
					/*
					// MAKE THE ENEMY PARALYZE
					// PROCESS STATUS FOR CERTAIN TIME -> IMPLEMENT IN UTURE
					ActorsParalyzed.Add(Actor);

					// Also Add a timer to reset the paralyze effect
					GetWorldTimerManager().SetTimer(ParalyzeTimeTimer, this,
						&AAbility_Paralyze::ResetParalyzeEffect, ParalyzeTimeDuration, true);
					*/
				}
			}
		}
	}
}

// 
void AAbility_Paralyze::ResetParalyzeEffect()
{
	// NO IDEA WHY THIS WAY, MAY DIRECTLY ActorsParalyzed ={}
	for (AActor* Actor : ActorsParalyzed)
	{
		// check if the enemy "valid"
		if (IsValid(Actor))
		{
			// reset its paralyze status
			ActorsParalyzed.Remove(Actor);
		}
	}
}

bool AAbility_Paralyze::EnemyInRange(UData_AbilityRequiredInfo* requiredInfo, AActor* Enemy)
{
	FVector EnemyLocation = Enemy->GetActorLocation();
	FVector EnemyDirection = EnemyLocation - requiredInfo->GetPlayerLocation();
	float Distance = EnemyDirection.Size();

	// Check if the actor is within the sphere radius
	if (Distance <= ConeLength)
	{
		// check if the actor is in cone -> compare 2 angles
		// the angles of player view and enemy vs angle
		FVector EnemyNormalDirection = EnemyDirection.GetSafeNormal();
		float DotProduct = FVector::DotProduct(EnemyNormalDirection, requiredInfo->GetPlayer()->GetForwardDirection());
		float Angle = FMath::RadiansToDegrees(FMath::Acos(DotProduct));

		if (Angle < ConeHalfAngle)
		{
			return true;
		}
	}
	return false;
}

