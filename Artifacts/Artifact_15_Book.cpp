// Fill out your copyright notice in the Description page of Project Settings.


#include "Artifact_15_Book.h"
#include "../Main.h"

// Sets default values
AArtifact_15_Book::AArtifact_15_Book()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ThisArtifactType = EArtifactType::EPickUp;
}

// Called when the game starts or when spawned
void AArtifact_15_Book::BeginPlay()
{
	Super::BeginPlay();

	//SetArtifact(EPickUp);
}

void AArtifact_15_Book::ApplyPickUpEffect(AMain* MainCharacter)
{
	MainCharacter->UpdateCharacterPowerUp(ratio);
}

void AArtifact_15_Book::EliminatePickUpEffect(AMain* MainCharacter)
{
	MainCharacter->UpdateCharacterPowerUp(1 / ratio);
}

void AArtifact_15_Book::UpdateRatio(float newRatio)
{
	ratio = newRatio;
}