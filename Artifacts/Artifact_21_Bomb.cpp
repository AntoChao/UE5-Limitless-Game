// Fill out your copyright notice in the Description page of Project Settings.


#include "Artifact_21_Bomb.h"
#include "../All_Enemies/EnemyClass.h"

// Sets default values
AArtifact_21_Bomb::AArtifact_21_Bomb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ThisArtifactType = EArtifactType::EAttack;
}

// Called when the game starts or when spawned
void AArtifact_21_Bomb::BeginPlay()
{
	Super::BeginPlay();

	//SetArtifact(Attack);
}

float AArtifact_21_Bomb::ApplyAttackEffect(float deltaDamage, FHitResult EnemyHit, AMain* PlayerMain)
{
	return deltaDamage * ratio;
}

void AArtifact_21_Bomb::UpdateRatio(float newRatio)
{
	ratio = newRatio;
}