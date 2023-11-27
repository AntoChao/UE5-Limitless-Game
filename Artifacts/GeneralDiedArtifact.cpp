// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneralDiedArtifact.h"
#include "../Main.h"
#include "../All_Enemies/EnemyClass.h"

// Sets default values
AGeneralDiedArtifact::AGeneralDiedArtifact()
{
	ThisArtifactType = EArtifactType::EDied;
}

// Called when the game starts or when spawned
void AGeneralDiedArtifact::BeginPlay()
{
	Super::BeginPlay();
	
	SetArtifact(EArtifactType::EDied);
}

// activate each time main receive attack, it lower the damage
bool AGeneralDiedArtifact::ApplyDiedEffect(AMain* PlayerMain)
{
	return true;
}