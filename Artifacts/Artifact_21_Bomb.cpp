// Fill out your copyright notice in the Description page of Project Settings.


#include "Artifact_21_Bomb.h"
#include "../All_Enemies/EnemyClass.h"

// Sets default values
AArtifact_21_Bomb::AArtifact_21_Bomb() {
 	
	ThisArtifactType = EArtifactType::EAttack;
}

float AArtifact_21_Bomb::ApplyAttackEffect(float deltaDamage, FHitResult EnemyHit, AMain* PlayerMain) {
	return deltaDamage * ratio;
}

void AArtifact_21_Bomb::UpdateRatio(float newRatio) {
	ratio = newRatio;
}