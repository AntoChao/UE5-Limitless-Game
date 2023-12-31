// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability_AlienGun.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Engine/EngineTypes.h"
#include "Engine/Blueprint.h"
#include "DrawDebugHelpers.h"
#include "Math/Vector.h"
#include "../AllCharactersClass.h"
#include "../Main.h"

// Sets default values
AAbility_AlienGun::AAbility_AlienGun(const class FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer) {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	
}

void AAbility_AlienGun::ActivateAbilityEffect(UData_AbilityRequiredInfo* requiredInfo) {
	// do the effect
	if (IsValid(requiredInfo->GetHitResult().GetActor())) {
		// will give error if somehow the traceline hits the main and not the enemy
		if (requiredInfo->GetHitResult().GetActor()->GetClass()->IsChildOf(AEnemyClass::StaticClass())) {
			AEnemyClass* EnemyDelta = Cast<AEnemyClass>(requiredInfo->GetHitResult().GetActor());

			EnemyDelta->UpdateHealthByMaxPercentage(-1.0f);
		}
	}
}