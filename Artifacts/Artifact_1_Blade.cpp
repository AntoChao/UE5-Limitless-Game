// Fill out your copyright notice in the Description page of Project Settings.


#include "Artifact_1_Blade.h"
#include "../Main.h"

// Sets default values
AArtifact_1_Blade::AArtifact_1_Blade()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ThisArtifactType = EArtifactType::EPickUp;
}

// Called when the game starts or when spawned
void AArtifact_1_Blade::BeginPlay()
{
	Super::BeginPlay();

	//SetArtifact(EPickUp);
}

void AArtifact_1_Blade::ApplyPickUpEffect(AMain* MainCharacter)
{
	MainCharacter->UpdateCharacterPowerUp(ratio);
}

void AArtifact_1_Blade::EliminatePickUpEffect(AMain* MainCharacter)
{
	MainCharacter->UpdateCharacterPowerUp(1 / ratio);
}

void AArtifact_1_Blade::UpdateRatio(float newRatio)
{
	ratio = newRatio;
}