// Fill out your copyright notice in the Description page of Project Settings.


#include "Artifact_26_Axe.h"
#include "../All_Enemies/EnemyClass.h"

// Sets default values
AArtifact_26_Axe::AArtifact_26_Axe() {
	ThisArtifactType = EArtifactType::EAttack;
}

float AArtifact_26_Axe::ApplyAttackEffect(float deltaDamage, FHitResult EnemyHit, AMain* PlayerMain) {
	return deltaDamage * ratio;
}

void AArtifact_26_Axe::UpdateRatio(float newRatio) {
	ratio = newRatio;
}