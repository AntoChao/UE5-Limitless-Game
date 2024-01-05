// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability_BulletTime.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Engine/EngineTypes.h"
#include "Engine/Blueprint.h"
#include "DrawDebugHelpers.h"
#include "../All_Enemies/EnemyClass.h"
#include "Math/Vector.h"
#include "../AllCharactersClass.h"
#include "../Main.h"

// Sets default values
AAbility_BulletTime::AAbility_BulletTime(const class FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer) {
}

// WHAT HAPPEND IF THE PLAYER USE THE ABILITY MULTI TIMES
void AAbility_BulletTime::ActivateAbilityEffect(UData_AbilityRequiredInfo* requiredInfo) { 

	if (IsValid(requiredInfo->GetWorldPointer())) {
		if (IsValid(requiredInfo->GetPlayer())) {
			CurrentWorld = requiredInfo->GetWorldPointer();
			MainPlayer = requiredInfo->GetPlayer();

			float WorldTimeDilation = CurrentWorld->GetWorldSettings()->TimeDilation;
			float playerDilation = MainPlayer->GetFForwardDilation();

			// Set the desired time dilation
			WorldTimeDilation = WorldTimeDilation * TimeDilationMultiplier;

			// Game end by time frezzed
			if (WorldTimeDilation <= MinTimeDilation) {
				GameOverTimeFreezed();
			}
			CurrentWorld->GetWorldSettings()->SetTimeDilation(WorldTimeDilation);
			
			// Set the player time dilation to normal
			MainPlayer->CustomTimeDilation = 1 / WorldTimeDilation * playerDilation;

			// if the bullet time niagara is still NOT spawned yet
			if (!MainPlayer->GetIsBulletTimeNiagaraSpawned()) {
				MainPlayer->AttachBulletTimeNiagara();
				MainPlayer->SetIsBulletTimeNiagaraSpawned(true);
			}

			MainPlayer->CustomRunResetDilationTimer(1 / WorldTimeDilation *
				BulletTimeDuration);
		}
	}
}

void AAbility_BulletTime::GameOverTimeFreezed() {
	if (IsValid(MainPlayer)) {
		MainPlayer->GameOverTimeFreezed();
	}	
}