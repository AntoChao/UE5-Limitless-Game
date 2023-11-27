// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneralPickUpArtifact.h"
#include "../Main.h"

// Sets default values
AGeneralPickUpArtifact::AGeneralPickUpArtifact()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ThisArtifactType = EArtifactType::EPickUp;
}

// Called when the game starts or when spawned
void AGeneralPickUpArtifact::BeginPlay()
{
	Super::BeginPlay();
	
	SetArtifact(EArtifactType::EPickUp);
}

// Called every frame
void AGeneralPickUpArtifact::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGeneralPickUpArtifact::ApplyPickUpEffect(AMain* MainCharacter)
{
	return;
}

void AGeneralPickUpArtifact::EliminatePickUpEffect(AMain* MainCharacter)
{
	return;
}