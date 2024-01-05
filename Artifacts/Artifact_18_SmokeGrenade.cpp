// Fill out your copyright notice in the Description page of Project Settings.


#include "Artifact_18_SmokeGrenade.h"
#include "../All_Enemies/EnemyClass.h"
#include "Math/UnrealMathUtility.h" // idk if is this file

// Sets default values
AArtifact_18_SmokeGrenade::AArtifact_18_SmokeGrenade() {
	ThisArtifactType = EArtifactType::EDefense;
}

float AArtifact_18_SmokeGrenade::ApplyDefenseEffect(float deltaDamage, AMain* PlayerMain) {
	float dodgeRoll = FMath::RandRange(1, 100);
	if (dodgeRatio <= dodgeRoll) {
		return 0.0f; // succefully dodged
	}
	else {
		return deltaDamage;
	}
}

void AArtifact_18_SmokeGrenade::UpdateRatio(float newRatio) {
	dodgeRatio = newRatio;
}