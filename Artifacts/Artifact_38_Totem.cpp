// Fill out your copyright notice in the Description page of Project Settings.


#include "Artifact_38_Totem.h"
#include "Math/UnrealMathUtility.h"
#include "../Main.h"

// Sets default values
AArtifact_38_Totem::AArtifact_38_Totem() {
	ThisArtifactType = EArtifactType::EPickUp;
}

void AArtifact_38_Totem::ApplyPickUpEffect(AMain* MainCharacter) {
	// NO IDEA IF IT IS ABLE TO GET THE WORLD IN ORDER TO SET TIMER

	// NEED TO IMPLEMENT THE FLY LOGIC
	MainCharacter->UpdateCalmGrowRate(ratio);
}

void AArtifact_38_Totem::EliminatePickUpEffect(AMain* MainCharacter) {
	MainCharacter->UpdateCalmGrowRate(-ratio);
}
