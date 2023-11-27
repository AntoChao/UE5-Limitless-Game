// Fill out your copyright notice in the Description page of Project Settings.


#include "Artifact_6_SniperRifle.h"
#include "../All_Enemies/EnemyClass.h"

// Sets default values
AArtifact_6_SniperRifle::AArtifact_6_SniperRifle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ThisArtifactType = EArtifactType::EAttack;
}

// Called when the game starts or when spawned
void AArtifact_6_SniperRifle::BeginPlay()
{
	Super::BeginPlay();

	//SetArtifact(Attack);
}

float AArtifact_6_SniperRifle::ApplyAttackEffect(float deltaDamage, FHitResult EnemyHit, AMain* PlayerMain)
{
	float Distance = EnemyHit.Distance / 100;
	if (Distance > distanceLimit)
	{
		return deltaDamage * ratio;
	}
	else
	{
		return deltaDamage;
	}
}

void AArtifact_6_SniperRifle::UpdateRatio(float newRatio)
{
	ratio = newRatio;
}