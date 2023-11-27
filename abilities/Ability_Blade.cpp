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
	:Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAbility_Blade::BeginPlay()
{
	Super::BeginPlay();
}

bool AAbility_Blade::AbilityRequirement(UData_AbilityRequiredInfo* requiredInfo)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("USING BLADE"));
	return true;
}

void AAbility_Blade::ActivateAbilityEffect(UData_AbilityRequiredInfo* requiredInfo)
{
	requiredInfoContainer = requiredInfo;

	// do the effect

}