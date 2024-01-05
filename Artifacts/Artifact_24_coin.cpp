// Fill out your copyright notice in the Description page of Project Settings.


#include "Artifact_24_Coin.h"
#include "../All_Enemies/EnemyClass.h"
#include "Math/UnrealMathUtility.h" // idk if is this file

// Sets default values
AArtifact_24_Coin::AArtifact_24_Coin()
{
	ThisArtifactType = EArtifactType::EAttack;
}

float AArtifact_24_Coin::ApplyAttackEffect(float deltaDamage, FHitResult EnemyHit, AMain* PlayerMain) {
	float deltaFrenzyChance = FMath::RandRange(1, 100);
	float deltaCalmChance = FMath::RandRange(1, 100);
	
	if (generateFrenzyProb >= deltaFrenzyChance) {
		//success
		PlayerMain->ChangeMainFrenzy(ratio);
	}
	if (generateCalmProb >= deltaCalmChance) {
		PlayerMain->ChangeMainCalm(ratio);
	}
	
	return deltaDamage;
}