// Fill out your copyright notice in the Description page of Project Settings.


#include "Artifact_12_pumpkin.h"
#include "../All_Enemies/EnemyClass.h"
#include "../Main.h"

// Sets default values
AArtifact_12_pumpkin::AArtifact_12_pumpkin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ThisArtifactType = EArtifactType::EAttack;
}

// Called when the game starts or when spawned
void AArtifact_12_pumpkin::BeginPlay()
{
	Super::BeginPlay();

	//SetArtifact(Attack);
}

float AArtifact_12_pumpkin::ApplyAttackEffect(float deltaDamage, FHitResult EnemyHit, AMain* PlayerMain)
{
	// no idea, should double check
	float inverseHealthProportion = 1 / (PlayerMain->GiveHealthPercentage());
	if (inverseHealthProportion < MaxBoost)
	{
		return deltaDamage * inverseHealthProportion;
	}
	else
	{
		return deltaDamage * ratioToScale;
	}
}

void AArtifact_12_pumpkin::UpdateRatio(float newMax)
{
	MaxBoost = newMax;
}