// Fill out your copyright notice in the Description page of Project Settings.


#include "Artifact_40_Fugu.h"
#include "Math/UnrealMathUtility.h"
#include "../Main.h"

// Sets default values
AArtifact_40_Fugu::AArtifact_40_Fugu()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ThisArtifactType = EArtifactType::EPickUp;
}

// Called when the game starts or when spawned
void AArtifact_40_Fugu::BeginPlay()
{
	Super::BeginPlay();
}

void AArtifact_40_Fugu::ApplyPickUpEffect(AMain* MainCharacter)
{
	// NO IDEA IF IT IS ABLE TO GET THE WORLD IN ORDER TO SET TIMER

	MainCharacter->UpdateCharacterPowerUpPercentage(ratio);
	MainCharacter->UpdateCharacterAttackRate(ratio);

	MainPlayer = MainCharacter;

	ShouldBeEliminateEffect = true;

	/* Cause Error -> as the duplicated does not have access to world
	GetWorldTimerManager().SetTimer(EliminateEffectTimer, this,
		&AArtifact_40_Fugu::EliminatePickUpEffectByTime, EffectDuration, true);
	*/
}

void AArtifact_40_Fugu::EliminatePickUpEffect(AMain* MainCharacter)
{
	if (ShouldBeEliminateEffect)
	{
		// No do anything -> when pick up is pick up
		MainCharacter->UpdateCharacterPowerUpPercentage(1 / ratio);
		MainCharacter->UpdateCharacterAttackRate(1 / ratio);
	}
}

void AArtifact_40_Fugu::EliminatePickUpEffectByTime()
{
	if (ShouldBeEliminateEffect)
	{
		// No do anything -> when pick up is pick up
		MainPlayer->UpdateCharacterPowerUpPercentage(1 / ratio);
		MainPlayer->UpdateCharacterAttackRate(1 / ratio);

		ShouldBeEliminateEffect = false;
	}
}