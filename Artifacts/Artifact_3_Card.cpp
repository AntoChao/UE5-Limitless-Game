// Fill out your copyright notice in the Description page of Project Settings.


#include "Artifact_3_Card.h"
#include "../Main.h"

// Sets default values
AArtifact_3_Card::AArtifact_3_Card() {
 	
	ThisArtifactType = EArtifactType::EPickUp;
}

void AArtifact_3_Card::ApplyPickUpEffect(AMain* MainCharacter) {
	MainCharacter->UpdateCharacterCritChance(ratio);
}

void AArtifact_3_Card::EliminatePickUpEffect(AMain* MainCharacter) {
	MainCharacter->UpdateCharacterCritChance(1 / ratio);
}

void AArtifact_3_Card::UpdateRatio(float newRatio) {
	ratio = newRatio;
}