// Fill out your copyright notice in the Description page of Project Settings.


#include "Artifact_35_Wings.h"
#include "Math/UnrealMathUtility.h"
#include "../Main.h"

// Sets default values
AArtifact_35_Wings::AArtifact_35_Wings()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ThisArtifactType = EArtifactType::EPickUp;
}

// Called when the game starts or when spawned
void AArtifact_35_Wings::BeginPlay()
{
	Super::BeginPlay();
}

void AArtifact_35_Wings::ApplyPickUpEffect(AMain* MainCharacter)
{
	// NO IDEA IF IT IS ABLE TO GET THE WORLD IN ORDER TO SET TIMER

	// NEED TO IMPLEMENT THE FLY LOGIC
	MainCharacter->SetIsAbleToFly(true);
	
	ShouldBeEliminateEffect = true;
	/*
	GetWorldTimerManager().SetTimer(EliminateEffectTimer, this,
		&AArtifact_35_Wings::EliminatePickUpEffectByTime, EffectDuration, true);
	*/
}

void AArtifact_35_Wings::EliminatePickUpEffect(AMain* MainCharacter)
{
	if (ShouldBeEliminateEffect)
	{
		MainCharacter->SetIsAbleToFly(false);
	}
}

void AArtifact_35_Wings::EliminatePickUpEffectByTime()
{
	if (ShouldBeEliminateEffect)
	{
		MainPlayer->SetIsAbleToFly(false);

		ShouldBeEliminateEffect = false;
	}
}