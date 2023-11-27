// Fill out your copyright notice in the Description page of Project Settings.


#include "Artifact_10_Dumbbell.h"
#include "../All_Enemies/EnemyClass.h"
#include "../Main.h"

// Sets default values
AArtifact_10_Dumbbell::AArtifact_10_Dumbbell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ThisArtifactType = EArtifactType::EPickUp;
}

// Called when the game starts or when spawned
void AArtifact_10_Dumbbell::BeginPlay()
{
	Super::BeginPlay();

	//SetArtifact(Attack);
}

void AArtifact_10_Dumbbell::ApplyPickUpEffect(AMain* MainCharacter)
{
	MainCharacter->UpdateMaxHealth(ratio, 0.0f);
}

void AArtifact_10_Dumbbell::EliminatePickUpEffect(AMain* MainCharacter)
{
	MainCharacter->UpdateMaxHealth(-ratio, 0.0f);
}

void AArtifact_10_Dumbbell::UpdateRatio(float newRatio)
{
	ratio = newRatio;
}