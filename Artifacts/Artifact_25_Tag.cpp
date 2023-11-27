// Fill out your copyright notice in the Description page of Project Settings.


#include "Artifact_25_Tag.h"
#include "../All_Enemies/EnemyClass.h"

// Sets default values
AArtifact_25_Tag::AArtifact_25_Tag()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ThisArtifactType = EArtifactType::EAttack;
}

// Called when the game starts or when spawned
void AArtifact_25_Tag::BeginPlay()
{
	Super::BeginPlay();

	//SetArtifact(Attack);
}

float AArtifact_25_Tag::ApplyAttackEffect(float deltaDamage, FHitResult EnemyHit, AMain* PlayerMain)
{
	return deltaDamage * ratio;
}

void AArtifact_25_Tag::UpdateRatio(float newRatio)
{
	ratio = newRatio;
}