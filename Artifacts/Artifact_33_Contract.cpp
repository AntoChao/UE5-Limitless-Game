// Fill out your copyright notice in the Description page of Project Settings.


#include "Artifact_33_Contract.h"
#include "Math/UnrealMathUtility.h"
#include "../Main.h"

// Sets default values
AArtifact_33_Contract::AArtifact_33_Contract() {
	ThisArtifactType = EArtifactType::EPickUp;
}

void AArtifact_33_Contract::ApplyPickUpEffect(AMain* MainCharacter) {
	// Lose 20% - 60& max hp randomly to gain x3 base damage 
	float PercentageHP2Lose = FMath::RandRange(20, 60);

	MainCharacter->UpdateMaxHealth(0.0f, PercentageHP2Lose/100.0f);
	MainCharacter->UpdateCharacterPowerUpPercentage(3.0f);
}

void AArtifact_33_Contract::EliminatePickUpEffect(AMain* MainCharacter) {
	// No do anything -> when pick up is pick up
	return;
}