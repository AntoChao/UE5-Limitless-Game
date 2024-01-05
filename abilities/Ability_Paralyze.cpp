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
	:Super(ObjectInitializer) {

}

/*  ActivateAbilityEffect has 3 process
*	Customize ability stats
*	Do the effect
*	Calculate feedback in order to return -> override all calculution base on ability
*/
void AAbility_Paralyze::ActivateAbilityEffect(UData_AbilityRequiredInfo* requiredInfo) {
	ParalyzeAllActorInCone(requiredInfo);
}


// I can use overlap to get all actors, but this is maybe better as it just run once
/* DECISION, FILTER -> APPLY EFFECT AFTERWARD OR APPLY DIRECTLY
1: Get All Actors in world
2: Filter all actors that are not enemies
3: Filter all actors that are not in sphere range
4: Filter all actors that are not in cone range
*/
void AAbility_Paralyze::ParalyzeAllActorInCone(UData_AbilityRequiredInfo* requiredInfo) {
	// Find all actors in world
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), ActorsInRange);

	for (AActor* Actor : ActorsInRange) {
		// check if actor is enemy:
		if (Actor->GetClass()->IsChildOf(AEnemyClass::StaticClass()) && IsValid(Actor)) {
			// is in range
			if (EnemyInRange(requiredInfo, Actor)) {
					
				// MAKE THE ENEMY PARALYZE
				AEnemyClass* AEnemy = Cast<AEnemyClass>(Actor);
				AEnemy->Immovilize(ParalyzeTime);

				EnemiesParalyzed.Add(AEnemy);
			}
		}
	}
}

bool AAbility_Paralyze::EnemyInRange(UData_AbilityRequiredInfo* requiredInfo, AActor* Enemy) {
	FVector EnemyLocation = Enemy->GetActorLocation();
	FVector EnemyDirection = EnemyLocation - requiredInfo->GetPlayerLocation();
	float Distance = EnemyDirection.Size();

	// Check if the actor is within the sphere radius
	if (Distance <= ConeLength) {
		// check if the actor is in cone -> compare 2 angles
		// the angles of player view and enemy vs angle
		FVector EnemyNormalDirection = EnemyDirection.GetSafeNormal();
		float DotProduct = FVector::DotProduct(EnemyNormalDirection, requiredInfo->GetPlayer()->GetForwardDirection());
		float Angle = FMath::RadiansToDegrees(FMath::Acos(DotProduct));

		if (Angle < ConeHalfAngle) {
			return true;
		}
	}
	return false;
}

