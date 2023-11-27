// Fill out your copyright notice in the Description page of Project Settings.


#include "Artifact_9_TinasDoggy.h"
#include "../Main.h"

// Sets default values
AArtifact_9_TinasDoggy::AArtifact_9_TinasDoggy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ThisArtifactType = EArtifactType::EPickUp;
}

// Called when the game starts or when spawned
void AArtifact_9_TinasDoggy::BeginPlay()
{
	Super::BeginPlay();

	//SetArtifact(Attack);
}

void AArtifact_9_TinasDoggy::ApplyPickUpEffect(AMain* MainCharacter)
{
	MainCharacter->UpdateCharacterAttackRate(ratio);
}

void AArtifact_9_TinasDoggy::EliminatePickUpEffect(AMain* MainCharacter)
{
	MainCharacter->UpdateCharacterAttackRate(1/ ratio);
}

void AArtifact_9_TinasDoggy::UpdateRatio(float newRatio)
{
	ratio = newRatio;
}