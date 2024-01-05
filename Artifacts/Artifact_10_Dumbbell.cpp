// Fill out your copyright notice in the Description page of Project Settings.


#include "Artifact_10_Dumbbell.h"
#include "../All_Enemies/EnemyClass.h"
#include "../Main.h"

// Sets default values
AArtifact_10_Dumbbell::AArtifact_10_Dumbbell() {
	ThisArtifactType = EArtifactType::EPickUp;
}

void AArtifact_10_Dumbbell::ApplyPickUpEffect(AMain* MainCharacter) {
	MainCharacter->UpdateMaxHealth(ratio, 0.0f);
}

void AArtifact_10_Dumbbell::EliminatePickUpEffect(AMain* MainCharacter) {
	MainCharacter->UpdateMaxHealth(-ratio, 0.0f);
}

void AArtifact_10_Dumbbell::UpdateRatio(float newRatio) {
	ratio = newRatio;
}