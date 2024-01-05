// Fill out your copyright notice in the Description page of Project Settings.


#include "Artifact_32_Medkit.h"
#include "../Main.h"

// Sets default values
AArtifact_32_Medkit::AArtifact_32_Medkit() {
 	
	ThisArtifactType = EArtifactType::EPickUp;
}

void AArtifact_32_Medkit::ApplyPickUpEffect(AMain* MainCharacter) {
	// 1.0f -> means max heal point
	MainCharacter->UpdateHealthByMaxPercentage(1.0f);
}

void AArtifact_32_Medkit::EliminatePickUpEffect(AMain* MainCharacter) {
	// No do anything -> when pick up is pick up
	return;
}