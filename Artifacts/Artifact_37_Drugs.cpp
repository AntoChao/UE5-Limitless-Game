// Fill out your copyright notice in the Description page of Project Settings.


#include "Artifact_37_Drugs.h"
#include "../All_Enemies/EnemyClass.h"

// Sets default values
AArtifact_37_Drugs::AArtifact_37_Drugs()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ThisArtifactType = EArtifactType::EAttack;
}

// Called when the game starts or when spawned
void AArtifact_37_Drugs::BeginPlay()
{
	Super::BeginPlay();

	//SetArtifact(Attack);
}

float AArtifact_37_Drugs::ApplyAttackEffect(float deltaDamage, FHitResult EnemyHit, AMain* PlayerMain)
{
	return deltaDamage * ratio;
}

void AArtifact_37_Drugs::UpdateRatio(float newRatio)
{
	ratio = newRatio;
}