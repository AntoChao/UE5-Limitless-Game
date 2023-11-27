// Fill out your copyright notice in the Description page of Project Settings.


#include "Artifact_5_Punch.h"
#include "../All_Enemies/EnemyClass.h"

// Sets default values
AArtifact_5_Punch::AArtifact_5_Punch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ThisArtifactType = EArtifactType::EAttack;
}

// Called when the game starts or when spawned
void AArtifact_5_Punch::BeginPlay()
{
	Super::BeginPlay();

	//SetArtifact(Attack);
}

float AArtifact_5_Punch::ApplyAttackEffect(float deltaDamage, FHitResult EnemyHit, AMain* PlayerMain)
{
	float Distance = EnemyHit.Distance / 100;
	if (Distance < distanceLimit)
	{
		return deltaDamage * ratio;
	}
	else
	{
		return deltaDamage;
	}
}

void AArtifact_5_Punch::UpdateRatio(float newRatio)
{
	ratio = newRatio;
}