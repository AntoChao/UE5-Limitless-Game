// Fill out your copyright notice in the Description page of Project Settings.


#include "Artifact_13_Bandana.h"
#include "../All_Enemies/EnemyClass.h"
#include "../Main.h"

// Sets default values
AArtifact_13_Bandana::AArtifact_13_Bandana() {
	ThisArtifactType = EArtifactType::EPickUp;
}

void AArtifact_13_Bandana::ApplyPickUpEffect(AMain* MainCharacter) {
	MainCharacter->UpdateDefaultMoveSpeed(ratio);
}

void AArtifact_13_Bandana::EliminatePickUpEffect(AMain* MainCharacter) {
	MainCharacter->UpdateDefaultMoveSpeed(1 / ratio);
}

void AArtifact_13_Bandana::UpdateRatio(float newRatio) {
	ratio = newRatio;
}