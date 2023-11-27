// Fill out your copyright notice in the Description page of Project Settings.


#include "Artifact_8_Picture.h"
#include "../Main.h"

// Sets default values
AArtifact_8_Picture::AArtifact_8_Picture()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ThisArtifactType = EArtifactType::EPickUp;
}

// Called when the game starts or when spawned
void AArtifact_8_Picture::BeginPlay()
{
	Super::BeginPlay();

	//SetArtifact(Attack);
}

void AArtifact_8_Picture::ApplyPickUpEffect(AMain* MainCharacter)
{
	MainCharacter->UpdateCharacterPowerUpPercentage(ratio);
}

void AArtifact_8_Picture::EliminatePickUpEffect(AMain* MainCharacter)
{
	MainCharacter->UpdateCharacterPowerUpPercentage(-ratio);
}

void AArtifact_8_Picture::UpdateRatio(float newRatio)
{
	ratio = newRatio;
}