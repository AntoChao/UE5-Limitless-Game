// Fill out your copyright notice in the Description page of Project Settings.


#include "Artifact_25_Tag.h"
#include "../All_Enemies/EnemyClass.h"

// Sets default values
AArtifact_25_Tag::AArtifact_25_Tag() {

	ThisArtifactType = EArtifactType::EAttack;
}

float AArtifact_25_Tag::ApplyAttackEffect(float deltaDamage, FHitResult EnemyHit, AMain* PlayerMain) {
	return deltaDamage * ratio;
}

void AArtifact_25_Tag::UpdateRatio(float newRatio) {
	ratio = newRatio;
}