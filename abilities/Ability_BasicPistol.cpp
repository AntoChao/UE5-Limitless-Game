// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability_BasicPistol.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Engine/EngineTypes.h"
#include "Engine/Blueprint.h"
#include "DrawDebugHelpers.h"
#include "Math/Vector.h"
#include "../AllCharactersClass.h"
#include "../Main.h"

// Sets default values
AAbility_BasicPistol::AAbility_BasicPistol(const class FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer) {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
}

/*ActivateAbilityEffect has 3 process
*	Customize ability stats
*	Do the effect
*	Calculate feedback in order to return -> override all calculution base on ability
*/
void AAbility_BasicPistol::ActivateAbilityEffect(UData_AbilityRequiredInfo* requiredInfo) {
	// do the effect
	if (IsValid(requiredInfo->GetHitResult().GetActor())) {
		// will give error if somehow the traceline hits the main and not the enemy
		if (requiredInfo->GetHitResult().GetActor()->GetClass()->IsChildOf(AEnemyClass::StaticClass())) {
			AEnemyClass* EnemyDelta = Cast<AEnemyClass>(requiredInfo->GetHitResult().GetActor());

			ApplyDamageToEnemy(EnemyDelta, CalculateSpecialDamage(requiredInfo), requiredInfo);
		}
	}
}

float AAbility_BasicPistol::CalculateSpecialDamage(UData_AbilityRequiredInfo* requiredInfo) {
	
	float Distance = requiredInfo->GetHitResult().Distance;
	float GeneralDamage = CalculateGeneralDamage(requiredInfo);

	// Calculate fall-off damage
	return FMath::Lerp(GeneralDamage, 0.0f,
		Distance / MaxDistance); // Linear fall-off
}