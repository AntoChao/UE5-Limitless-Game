// Fill out your copyright notice in the Description page of Project Settings.


#include "Artifact_34_Caffeine.h"
#include "Math/UnrealMathUtility.h"
#include "../Main.h"

// Sets default values
AArtifact_34_Caffeine::AArtifact_34_Caffeine() {
	ThisArtifactType = EArtifactType::EPickUp;
}

void AArtifact_34_Caffeine::ApplyPickUpEffect(AMain* MainCharacter) {
	// NO IDEA IF IT IS ABLE TO GET THE WORLD IN ORDER TO SET TIMER

	MainCharacter->UpdateCharacterPowerUpPercentage(ratio);
	MainCharacter->UpdateCharacterAttackRate(ratio);

	MainPlayer = MainCharacter;

	ShouldBeEliminateEffect = true;
}

void AArtifact_34_Caffeine::EliminatePickUpEffect(AMain* MainCharacter) {
	if (ShouldBeEliminateEffect) {
		// No do anything -> when pick up is pick up
		MainCharacter->UpdateCharacterPowerUpPercentage(1 / ratio);
		MainCharacter->UpdateCharacterAttackRate(1 / ratio);
	}
}

void AArtifact_34_Caffeine::EliminatePickUpEffectByTime() {
	if (ShouldBeEliminateEffect) {
		// No do anything -> when pick up is pick up
		MainPlayer->UpdateCharacterPowerUpPercentage(1 / ratio);
		MainPlayer->UpdateCharacterAttackRate(1 / ratio);

		ShouldBeEliminateEffect = false;
	}
}