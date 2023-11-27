// Fill out your copyright notice in the Description page of Project Settings.


#include "Artifact_38_Totem.h"
#include "Math/UnrealMathUtility.h"
#include "../Main.h"

// Sets default values
AArtifact_38_Totem::AArtifact_38_Totem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ThisArtifactType = EArtifactType::EPickUp;
}

// Called when the game starts or when spawned
void AArtifact_38_Totem::BeginPlay()
{
	Super::BeginPlay();
}

void AArtifact_38_Totem::ApplyPickUpEffect(AMain* MainCharacter)
{
	// NO IDEA IF IT IS ABLE TO GET THE WORLD IN ORDER TO SET TIMER

	// NEED TO IMPLEMENT THE FLY LOGIC
	MainCharacter->UpdateCalmGrowRate(ratio);
}

void AArtifact_38_Totem::EliminatePickUpEffect(AMain* MainCharacter)
{
	MainCharacter->UpdateCalmGrowRate(-ratio);
}
