// Fill out your copyright notice in the Description page of Project Settings.


#include "Artifact_29_Rune.h"
#include "../All_Enemies/EnemyClass.h"

// Sets default values
AArtifact_29_Rune::AArtifact_29_Rune() {
	ThisArtifactType = EArtifactType::ECost;
}

float AArtifact_29_Rune::ApplyFrenzyCostEffect(float FrenzyCost, AMain* MainCharacter) {
	return 0.0f;
}

float AArtifact_29_Rune::ApplyCalmCostEffect(float FrenzyCost, AMain* MainCharacter) {
	return 0.0f;
}