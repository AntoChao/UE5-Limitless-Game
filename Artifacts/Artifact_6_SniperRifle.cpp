// Fill out your copyright notice in the Description page of Project Settings.


#include "Artifact_6_SniperRifle.h"
#include "../All_Enemies/EnemyClass.h"

// Sets default values
AArtifact_6_SniperRifle::AArtifact_6_SniperRifle() {
 	
	ThisArtifactType = EArtifactType::EAttack;
}

float AArtifact_6_SniperRifle::ApplyAttackEffect(float deltaDamage, FHitResult EnemyHit, AMain* PlayerMain) {
	float Distance = EnemyHit.Distance / 100;
	if (Distance > distanceLimit) {
		return deltaDamage * ratio;
	}
	else {
		return deltaDamage;
	}
}

void AArtifact_6_SniperRifle::UpdateRatio(float newRatio) {
	ratio = newRatio;
}