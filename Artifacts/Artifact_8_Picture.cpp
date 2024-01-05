// Fill out your copyright notice in the Description page of Project Settings.


#include "Artifact_8_Picture.h"
#include "../Main.h"

// Sets default values
AArtifact_8_Picture::AArtifact_8_Picture() {
 	
	ThisArtifactType = EArtifactType::EPickUp;
}

void AArtifact_8_Picture::ApplyPickUpEffect(AMain* MainCharacter) {
	MainCharacter->UpdateCharacterPowerUpPercentage(ratio);
}

void AArtifact_8_Picture::EliminatePickUpEffect(AMain* MainCharacter) {
	MainCharacter->UpdateCharacterPowerUpPercentage(-ratio);
}

void AArtifact_8_Picture::UpdateRatio(float newRatio) {
	ratio = newRatio;
}