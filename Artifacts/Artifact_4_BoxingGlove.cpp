// Fill out your copyright notice in the Description page of Project Settings.


#include "Artifact_4_BoxingGlove.h"
#include "../All_Enemies/EnemyClass.h"

// Sets default values
AArtifact_4_BoxingGlove::AArtifact_4_BoxingGlove()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ThisArtifactType = EArtifactType::EAttack;
}

// Called when the game starts or when spawned
void AArtifact_4_BoxingGlove::BeginPlay()
{
	Super::BeginPlay();

	//SetArtifact(Attack);
}

float AArtifact_4_BoxingGlove::ApplyAttackEffect(float deltaDamage, FHitResult EnemyHit, AMain* PlayerMain)
{
	AEnemyClass* Enemy = Cast<AEnemyClass>(EnemyHit.GetActor());

	if (Enemy->GiveHealthPercentage() == 1.0f)
	{
		return deltaDamage * ratio;
	}
	else
	{
		return deltaDamage;
	}
	
}

void AArtifact_4_BoxingGlove::UpdateRatio(float newRatio)
{
	ratio = newRatio;
}