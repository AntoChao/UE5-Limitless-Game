// Fill out your copyright notice in the Description page of Project Settings.


#include "Artifact_31_Smelting.h"
#include "../Main.h"

// Sets default values
AArtifact_31_Smelting::AArtifact_31_Smelting()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ThisArtifactType = EArtifactType::EPickUp;
}

// Called when the game starts or when spawned
void AArtifact_31_Smelting::BeginPlay()
{
	Super::BeginPlay();

	//SetArtifact(EPickUp);
}

void AArtifact_31_Smelting::ApplyPickUpEffect(AMain* MainCharacter)
{
	MainCharacter->UpdateCharacterCritMultiplier(ratio);
}

void AArtifact_31_Smelting::EliminatePickUpEffect(AMain* MainCharacter)
{
	MainCharacter->UpdateCharacterCritMultiplier(1 / ratio);
}

void AArtifact_31_Smelting::UpdateRatio(float newRatio)
{
	ratio = newRatio;
}