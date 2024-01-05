// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability_Sniper.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Engine/EngineTypes.h"
#include "Engine/Blueprint.h"
#include "DrawDebugHelpers.h"
#include "../All_Enemies/EnemyClass.h"
#include "Math/Vector.h"
#include "../AllCharactersClass.h"
#include "../Main.h"

// Sets default values
AAbility_Sniper::AAbility_Sniper(const class FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer) {
}

void AAbility_Sniper::ActivateAbilityEffect(UData_AbilityRequiredInfo* requiredInfo) {
	// do the effect
	if (IsValid(requiredInfo->GetHitResult().GetActor())) {
		if (requiredInfo->GetHitResult().GetActor()->GetClass()->IsChildOf(AEnemyClass::StaticClass())) {
			AEnemyClass* EnemyDelta = Cast<AEnemyClass>(requiredInfo->GetHitResult().GetActor());

			ApplyDamageToEnemy(EnemyDelta, CalculateSpecialDamage(requiredInfo), requiredInfo);
		}
	}	
}

float AAbility_Sniper::CalculateSpecialDamage(UData_AbilityRequiredInfo* requiredInfo) {
	
	float Distance = requiredInfo->GetHitResult().Distance;
	float GeneralDamage = CalculateGeneralDamage(requiredInfo);

	float DamageDealed = FMath::Lerp(GeneralDamage, 0.0f, Distance / MaxDistance);

	if (DamageDealed >= 0) {
		return DamageDealed;
	}
	else {
		return 0;
	}
}
