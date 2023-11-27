// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneralDefenseArtifact.h"
#include "../Main.h"
#include "../All_Enemies/EnemyClass.h"

// Sets default values
AGeneralDefenseArtifact::AGeneralDefenseArtifact()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ThisArtifactType = EArtifactType::EDefense;
}

// Called when the game starts or when spawned
void AGeneralDefenseArtifact::BeginPlay()
{
	Super::BeginPlay();
	
	SetArtifact(EArtifactType::EDefense);
}

// activate each time main receive attack, it lower the damage
float AGeneralDefenseArtifact::ApplyDefenseEffect(float deltaDamage, AMain* PlayerMain)
{
	return deltaDamage;
}