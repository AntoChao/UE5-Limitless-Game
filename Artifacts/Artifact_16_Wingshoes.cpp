// Fill out your copyright notice in the Description page of Project Settings.


#include "Artifact_16_Wingshoes.h"
#include "../Main.h"

// Sets default values
AArtifact_16_Wingshoes::AArtifact_16_Wingshoes()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ThisArtifactType = EArtifactType::EPickUp;
}

// Called when the game starts or when spawned
void AArtifact_16_Wingshoes::BeginPlay()
{
	Super::BeginPlay();

	//SetArtifact(EPickUp);
}

void AArtifact_16_Wingshoes::ApplyPickUpEffect(AMain* MainCharacter)
{
	MainCharacter->UpdateCharacterPowerUp(ratio);
}

void AArtifact_16_Wingshoes::EliminatePickUpEffect(AMain* MainCharacter)
{
	MainCharacter->UpdateCharacterPowerUp(1 / ratio);
}

void AArtifact_16_Wingshoes::UpdateRatio(float newRatio)
{
	ratio = newRatio;
}