// Fill out your copyright notice in the Description page of Project Settings.


#include "Artifact_27_Instinct.h"
#include "../All_Enemies/EnemyClass.h"
#include "../Main.h"
#include "Math/UnrealMathUtility.h" // idk if is this file

// Sets default values
AArtifact_27_Instinct::AArtifact_27_Instinct()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ThisArtifactType = EArtifactType::EDefense;
}

// Called when the game starts or when spawned
void AArtifact_27_Instinct::BeginPlay()
{
	Super::BeginPlay();

	//SetArtifact(Attack);
}

float AArtifact_27_Instinct::ApplyDefenseEffect(float deltaDamage, AMain* PlayerMain)
{
	// it is wrong the logic, need to test
	float inverseHealthProportion = 1 / (PlayerMain->GiveHealthPercentage());
	if (inverseHealthProportion < MaxRatioBoost)
	{
		PlayerMain->UpdateDefaultMoveSpeed(inverseHealthProportion);
	}
	else
	{
		PlayerMain->UpdateDefaultMoveSpeed(ratioToSpeed);
	}
	return deltaDamage;
}

void AArtifact_27_Instinct::UpdateRatio(float newRatio)
{
	MaxRatioBoost = newRatio;
}