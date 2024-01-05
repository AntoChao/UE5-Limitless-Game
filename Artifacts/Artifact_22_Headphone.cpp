// Fill out your copyright notice in the Description page of Project Settings.


#include "Artifact_22_Headphone.h"
#include "../Main.h"

// Sets default values
AArtifact_22_Headphone::AArtifact_22_Headphone() {

	ThisArtifactType = EArtifactType::EPickUp;
}

void AArtifact_22_Headphone::ApplyPickUpEffect(AMain* MainCharacter) {
	MainCharacter->UpdateCharacterPowerUp(ratio);
}

void AArtifact_22_Headphone::EliminatePickUpEffect(AMain* MainCharacter) {
	MainCharacter->UpdateCharacterPowerUp(1 / ratio);
}

void AArtifact_22_Headphone::UpdateRatio(float newRatio) {
	ratio = newRatio;
}