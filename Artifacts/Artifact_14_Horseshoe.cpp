// Fill out your copyright notice in the Description page of Project Settings.


#include "Artifact_14_Horseshoe.h"
#include "../All_Enemies/EnemyClass.h"
#include "../Main.h"

// Sets default values
AArtifact_14_Horseshoe::AArtifact_14_Horseshoe()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ThisArtifactType = EArtifactType::EPickUp;
}

// Called when the game starts or when spawned
void AArtifact_14_Horseshoe::BeginPlay()
{
	Super::BeginPlay();

	//SetArtifact(Attack);
}

void AArtifact_14_Horseshoe::ApplyPickUpEffect(AMain* MainCharacter)
{
	MainCharacter->ReceiveSpeedBoost(ratio, ArtifactDuration);
}

void AArtifact_14_Horseshoe::EliminatePickUpEffect(AMain* MainCharacter)
{
	MainCharacter->ReceiveSpeedBoost(1 / ratio, ArtifactDuration);
}

void AArtifact_14_Horseshoe::UpdateRatio(float newRatio)
{
	ratio = newRatio;
}