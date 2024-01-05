// Fill out your copyright notice in the Description page of Project Settings.


#include "Artifact_11_Dice.h"
#include "../All_Enemies/EnemyClass.h"

// Sets default values
AArtifact_11_Dice::AArtifact_11_Dice() {
	ThisArtifactType = EArtifactType::ECost;
}

float AArtifact_11_Dice::ApplyFrenzyCostEffect(float FrenzyCost, AMain* MainCharacter) {
	return 0.0f;
}

float AArtifact_11_Dice::ApplyCalmCostEffect(float FrenzyCost, AMain* MainCharacter) {
	return 0.0f;
}