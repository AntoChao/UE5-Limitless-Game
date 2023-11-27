// Fill out your copyright notice in the Description page of Project Settings.


#include "Artifact_13_Bandana.h"
#include "../All_Enemies/EnemyClass.h"
#include "../Main.h"

// Sets default values
AArtifact_13_Bandana::AArtifact_13_Bandana()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ThisArtifactType = EArtifactType::EPickUp;
}

// Called when the game starts or when spawned
void AArtifact_13_Bandana::BeginPlay()
{
	Super::BeginPlay();

	//SetArtifact(Attack);
}

void AArtifact_13_Bandana::ApplyPickUpEffect(AMain* MainCharacter)
{
	MainCharacter->UpdateDefaultMoveSpeed(ratio);
}

void AArtifact_13_Bandana::EliminatePickUpEffect(AMain* MainCharacter)
{
	MainCharacter->UpdateDefaultMoveSpeed(1 / ratio);
}

void AArtifact_13_Bandana::UpdateRatio(float newRatio)
{
	ratio = newRatio;
}