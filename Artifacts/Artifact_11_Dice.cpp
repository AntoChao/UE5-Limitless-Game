// Fill out your copyright notice in the Description page of Project Settings.


#include "Artifact_11_Dice.h"
#include "../All_Enemies/EnemyClass.h"

// Sets default values
AArtifact_11_Dice::AArtifact_11_Dice()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ThisArtifactType = EArtifactType::ECost;
}

// Called when the game starts or when spawned
void AArtifact_11_Dice::BeginPlay()
{
	Super::BeginPlay();

	//SetArtifact(Attack);
}

float AArtifact_11_Dice::ApplyFrenzyCostEffect(float FrenzyCost, AMain* MainCharacter)
{
	return 0.0f;
}

float AArtifact_11_Dice::ApplyCalmCostEffect(float FrenzyCost, AMain* MainCharacter)
{
	return 0.0f;
}