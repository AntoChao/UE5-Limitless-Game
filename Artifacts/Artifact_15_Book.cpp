// Fill out your copyright notice in the Description page of Project Settings.


#include "Artifact_15_Book.h"
#include "../Main.h"

// Sets default values
AArtifact_15_Book::AArtifact_15_Book() {
 	
	ThisArtifactType = EArtifactType::EPickUp;
}

void AArtifact_15_Book::ApplyPickUpEffect(AMain* MainCharacter) {
	MainCharacter->UpdateCharacterPowerUp(ratio);
}

void AArtifact_15_Book::EliminatePickUpEffect(AMain* MainCharacter) {
	MainCharacter->UpdateCharacterPowerUp(1 / ratio);
}

void AArtifact_15_Book::UpdateRatio(float newRatio) {
	ratio = newRatio;
}