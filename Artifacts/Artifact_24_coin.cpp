// Fill out your copyright notice in the Description page of Project Settings.


#include "Artifact_24_Coin.h"
#include "../All_Enemies/EnemyClass.h"
#include "Math/UnrealMathUtility.h" // idk if is this file

// Sets default values
AArtifact_24_Coin::AArtifact_24_Coin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ThisArtifactType = EArtifactType::EAttack;
}

// Called when the game starts or when spawned
void AArtifact_24_Coin::BeginPlay()
{
	Super::BeginPlay();

	//SetArtifact(Attack);
}

float AArtifact_24_Coin::ApplyAttackEffect(float deltaDamage, FHitResult EnemyHit, AMain* PlayerMain)
{
	float deltaFrenzyChance = FMath::RandRange(1, 100);
	float deltaCalmChance = FMath::RandRange(1, 100);
	
	if (generateFrenzyProb >= deltaFrenzyChance) //success
	{
		PlayerMain->ChangeMainFrenzy(ratio);
	}
	if (generateCalmProb >= deltaCalmChance)
	{
		PlayerMain->ChangeMainCalm(ratio);
	}
	
	return deltaDamage;
}