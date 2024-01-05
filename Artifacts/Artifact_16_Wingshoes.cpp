// Fill out your copyright notice in the Description page of Project Settings.


#include "Artifact_16_Wingshoes.h"
#include "../Main.h"

// Sets default values
AArtifact_16_Wingshoes::AArtifact_16_Wingshoes() {
	ThisArtifactType = EArtifactType::EPickUp;
}

void AArtifact_16_Wingshoes::ApplyPickUpEffect(AMain* MainCharacter) {
	MainCharacter->UpdateCharacterPowerUp(ratio);
}

void AArtifact_16_Wingshoes::EliminatePickUpEffect(AMain* MainCharacter) {
	MainCharacter->UpdateCharacterPowerUp(1 / ratio);
}

void AArtifact_16_Wingshoes::UpdateRatio(float newRatio) {
	ratio = newRatio;
}