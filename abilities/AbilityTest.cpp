// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityTest.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Engine/EngineTypes.h"
#include "DrawDebugHelpers.h"

// Sets default values
AAbilityTest::AAbilityTest(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void AAbilityTest::ActivateAbilityEffect(UData_AbilityRequiredInfo* requiredInfo)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("using test ability lv 1"));
}