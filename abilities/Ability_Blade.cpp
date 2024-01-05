// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability_Blade.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Engine/EngineTypes.h"
#include "Engine/Blueprint.h"
#include "DrawDebugHelpers.h"
#include "../AllCharactersClass.h"
#include "../Main.h"


// Sets default values
AAbility_Blade::AAbility_Blade(const class FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer) {
}

void AAbility_Blade::ActivateAbilityEffect(UData_AbilityRequiredInfo* requiredInfo) {
	requiredInfoContainer = requiredInfo;

	// do the effect
}