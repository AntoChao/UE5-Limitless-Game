// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability_FForward.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Engine/EngineTypes.h"
#include "Engine/Blueprint.h"
#include "DrawDebugHelpers.h"
#include "../All_Enemies/EnemyClass.h"
#include "Math/Vector.h"
#include "../AllCharactersClass.h"
#include "../Main.h"

// Sets default values
AAbility_FForward::AAbility_FForward(const class FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer) {
}

void AAbility_FForward::ActivateAbilityEffect(UData_AbilityRequiredInfo* requiredInfo) {
	// do the effect
	if (IsValid(requiredInfo->GetPlayer())) {
		MainPlayer = requiredInfo->GetPlayer();

		float CurrentTimeDilation = requiredInfo->GetPlayer()->CustomTimeDilation;
		CurrentTimeDilation = CurrentTimeDilation * TimeDilationMultiplier;

		MainPlayer->CustomTimeDilation = CurrentTimeDilation;
		MainPlayer->SetFForwardDilation(CurrentTimeDilation);

		// if the bullet time niagara is still NOT spawned yet
		if (!MainPlayer->GetIsFForwardNiagaraSpawned()) {
			MainPlayer->AttachFForwardNiagara();
			MainPlayer->SetIsFForwardNiagaraSpawned(true);
		}
			
		MainPlayer->CustomRunResetDilationTimer(FFowardDuration);
	}
}