// Fill out your copyright notice in the Description page of Project Settings.


#include "Artifact_35_Wings.h"
#include "Math/UnrealMathUtility.h"
#include "../Main.h"

// Sets default values
AArtifact_35_Wings::AArtifact_35_Wings() {
	ThisArtifactType = EArtifactType::EPickUp;
}

void AArtifact_35_Wings::ApplyPickUpEffect(AMain* MainCharacter) {
	// NO IDEA IF IT IS ABLE TO GET THE WORLD IN ORDER TO SET TIMER

	// NEED TO IMPLEMENT THE FLY LOGIC
	MainCharacter->SetIsAbleToFly(true);
	
	ShouldBeEliminateEffect = true;
}

void AArtifact_35_Wings::EliminatePickUpEffect(AMain* MainCharacter) {
	if (ShouldBeEliminateEffect) {
		MainCharacter->SetIsAbleToFly(false);
	}
}

void AArtifact_35_Wings::EliminatePickUpEffectByTime() {
	if (ShouldBeEliminateEffect) {
		MainPlayer->SetIsAbleToFly(false);

		ShouldBeEliminateEffect = false;
	}
}