// Fill out your copyright notice in the Description page of Project Settings.


#include "Artifact_2_SaoBlade.h"
#include "../All_Enemies/EnemyClass.h"

// Sets default values
AArtifact_2_SaoBlade::AArtifact_2_SaoBlade() {
	ThisArtifactType = EArtifactType::EAttack;
}

float AArtifact_2_SaoBlade::ApplyAttackEffect(float deltaDamage, FHitResult EnemyHit, AMain* PlayerMain) {
	return deltaDamage * ratio;
}

void AArtifact_2_SaoBlade::UpdateRatio(float newRatio) {
	ratio = newRatio;
}