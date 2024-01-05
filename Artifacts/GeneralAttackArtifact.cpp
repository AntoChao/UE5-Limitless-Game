// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneralAttackArtifact.h"
#include "../Main.h"
#include "../All_Enemies/EnemyClass.h"

// Sets default values
AGeneralAttackArtifact::AGeneralAttackArtifact() {
 	
	PrimaryActorTick.bCanEverTick = true;

	ThisArtifactType = EArtifactType::EAttack;
}

// Called when the game starts or when spawned
void AGeneralAttackArtifact::BeginPlay() {
	Super::BeginPlay();
	
	SetArtifact(EArtifactType::EAttack);
}

float AGeneralAttackArtifact::ApplyAttackEffect(float deltaDamage, FHitResult EnemyHit, AMain* PlayerMain) {
	return deltaDamage;
}