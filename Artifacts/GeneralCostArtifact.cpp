// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneralCostArtifact.h"
#include "../Main.h"
#include "../All_Enemies/EnemyClass.h"

// Sets default values
AGeneralCostArtifact::AGeneralCostArtifact()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ThisArtifactType = EArtifactType::ECost;
}

// Called when the game starts or when spawned
void AGeneralCostArtifact::BeginPlay()
{
	Super::BeginPlay();
	
	SetArtifact(EArtifactType::ECost);
}

float AGeneralCostArtifact::ApplyFrenzyCostEffect(float FrenzyCost, AMain* MainCharacter)
{
	return FrenzyCost;
}

float AGeneralCostArtifact::ApplyCalmCostEffect(float CalmCost, AMain* MainCharacter)
{
	return CalmCost;
}