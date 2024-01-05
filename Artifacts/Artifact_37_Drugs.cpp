// Fill out your copyright notice in the Description page of Project Settings.


#include "Artifact_37_Drugs.h"
#include "../All_Enemies/EnemyClass.h"

// Sets default values
AArtifact_37_Drugs::AArtifact_37_Drugs() {

	ThisArtifactType = EArtifactType::EAttack;
}

float AArtifact_37_Drugs::ApplyAttackEffect(float deltaDamage, FHitResult EnemyHit, AMain* PlayerMain) {
	return deltaDamage * ratio;
}

void AArtifact_37_Drugs::UpdateRatio(float newRatio) {
	ratio = newRatio;
}