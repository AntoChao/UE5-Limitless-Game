// Fill out your copyright notice in the Description page of Project Settings.


#include "Artifact_36_Cigaratte.h"
#include "Math/UnrealMathUtility.h"
#include "../Main.h"

// Sets default values
AArtifact_36_Cigaratte::AArtifact_36_Cigaratte() {
 	
	ThisArtifactType = EArtifactType::EPickUp;
}

void AArtifact_36_Cigaratte::ApplyPickUpEffect(AMain* MainCharacter) {
	// NO IDEA IF IT IS ABLE TO GET THE WORLD IN ORDER TO SET TIMER

	// NEED TO IMPLEMENT THE FLY LOGIC
	MainCharacter->UpdateCalmGrowRate(ratio);
}

void AArtifact_36_Cigaratte::EliminatePickUpEffect(AMain* MainCharacter) {
	MainCharacter->UpdateCalmGrowRate(-ratio);
}
