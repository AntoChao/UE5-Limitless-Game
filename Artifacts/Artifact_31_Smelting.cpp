// Fill out your copyright notice in the Description page of Project Settings.


#include "Artifact_31_Smelting.h"
#include "../Main.h"

// Sets default values
AArtifact_31_Smelting::AArtifact_31_Smelting() {
	ThisArtifactType = EArtifactType::EPickUp;
}

void AArtifact_31_Smelting::ApplyPickUpEffect(AMain* MainCharacter) {
	MainCharacter->UpdateCharacterCritMultiplier(ratio);
}

void AArtifact_31_Smelting::EliminatePickUpEffect(AMain* MainCharacter) {
	MainCharacter->UpdateCharacterCritMultiplier(1 / ratio);
}

void AArtifact_31_Smelting::UpdateRatio(float newRatio) {
	ratio = newRatio;
}