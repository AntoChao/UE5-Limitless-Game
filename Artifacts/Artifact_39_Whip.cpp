// Fill out your copyright notice in the Description page of Project Settings.


#include "Artifact_39_Whip.h"
#include "../All_Enemies/EnemyClass.h"
#include "Math/UnrealMathUtility.h" // idk if is this file

// Sets default values
AArtifact_39_Whip::AArtifact_39_Whip() {
	ThisArtifactType = EArtifactType::EDefense;
}

float AArtifact_39_Whip::ApplyDefenseEffect(float deltaDamage, AMain* PlayerMain) {
	// it is wrong the logic, need to test
	float inverseHealthProportion = 1 / (PlayerMain->GiveHealthPercentage());
	if (inverseHealthProportion < MaxRatioBoost) {
		PlayerMain->UpdateDefaultMoveSpeed(inverseHealthProportion);
	}
	else {
		PlayerMain->UpdateDefaultMoveSpeed(ratioToSpeed);
	}
	return deltaDamage;
}

void AArtifact_39_Whip::UpdateRatio(float newRatio) {
	MaxRatioBoost = newRatio;
}