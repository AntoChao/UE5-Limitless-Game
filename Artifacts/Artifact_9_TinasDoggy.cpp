// Fill out your copyright notice in the Description page of Project Settings.


#include "Artifact_9_TinasDoggy.h"
#include "../Main.h"

// Sets default values
AArtifact_9_TinasDoggy::AArtifact_9_TinasDoggy() {
	ThisArtifactType = EArtifactType::EPickUp;
}


void AArtifact_9_TinasDoggy::ApplyPickUpEffect(AMain* MainCharacter) {
	MainCharacter->UpdateCharacterAttackRate(ratio);
}

void AArtifact_9_TinasDoggy::EliminatePickUpEffect(AMain* MainCharacter) {
	MainCharacter->UpdateCharacterAttackRate(1/ ratio);
}

void AArtifact_9_TinasDoggy::UpdateRatio(float newRatio) {
	ratio = newRatio;
}