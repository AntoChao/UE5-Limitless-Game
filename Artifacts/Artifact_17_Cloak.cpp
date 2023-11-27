// Fill out your copyright notice in the Description page of Project Settings.


#include "Artifact_17_Cloak.h"
#include "../All_Enemies/EnemyClass.h"

// Sets default values
AArtifact_17_Cloak::AArtifact_17_Cloak()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ThisArtifactType = EArtifactType::EDefense;
}

// Called when the game starts or when spawned
void AArtifact_17_Cloak::BeginPlay()
{
	Super::BeginPlay();

	//SetArtifact(Attack);
}

float AArtifact_17_Cloak::ApplyDefenseEffect(float deltaDamage, AMain* PlayerMain)
{
	//float deltaHealth = PlayerMain->GetCharacterHealth();
	if (deltaDamage >= PlayerMain->GetCharacterHealth())
	{
		return 0.0f; // not going to do any damage
	}
	else
	{
		return deltaDamage;
	}
}

void AArtifact_17_Cloak::UpdateRatio(float newRatio)
{
	ratio = newRatio;
}