// Fill out your copyright notice in the Description page of Project Settings.


#include "Artifact_29_Rune.h"
#include "../All_Enemies/EnemyClass.h"

// Sets default values
AArtifact_29_Rune::AArtifact_29_Rune()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ThisArtifactType = EArtifactType::ECost;
}

// Called when the game starts or when spawned
void AArtifact_29_Rune::BeginPlay()
{
	Super::BeginPlay();

	//SetArtifact(Attack);
}

float AArtifact_29_Rune::ApplyFrenzyCostEffect(float FrenzyCost, AMain* MainCharacter)
{
	return 0.0f;
}

float AArtifact_29_Rune::ApplyCalmCostEffect(float FrenzyCost, AMain* MainCharacter)
{
	return 0.0f;
}