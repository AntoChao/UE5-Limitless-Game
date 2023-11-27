// Fill out your copyright notice in the Description page of Project Settings.


#include "Artifact_36_Cigaratte.h"
#include "Math/UnrealMathUtility.h"
#include "../Main.h"

// Sets default values
AArtifact_36_Cigaratte::AArtifact_36_Cigaratte()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ThisArtifactType = EArtifactType::EPickUp;
}

// Called when the game starts or when spawned
void AArtifact_36_Cigaratte::BeginPlay()
{
	Super::BeginPlay();
}

void AArtifact_36_Cigaratte::ApplyPickUpEffect(AMain* MainCharacter)
{
	// NO IDEA IF IT IS ABLE TO GET THE WORLD IN ORDER TO SET TIMER

	// NEED TO IMPLEMENT THE FLY LOGIC
	MainCharacter->UpdateCalmGrowRate(ratio);
}

void AArtifact_36_Cigaratte::EliminatePickUpEffect(AMain* MainCharacter)
{
	MainCharacter->UpdateCalmGrowRate(-ratio);
}
