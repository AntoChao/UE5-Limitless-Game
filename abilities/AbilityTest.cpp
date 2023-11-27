// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityTest.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Engine/EngineTypes.h"
#include "DrawDebugHelpers.h"

// Sets default values
AAbilityTest::AAbilityTest(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	//AAbilityTest::Super(ObjectInitializer);
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//feedBackContainer = NewObject<UData_AbilityFeedBackInfo>();
}

// Called when the game starts or when spawned
void AAbilityTest::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AAbilityTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Define its requirement
bool AAbilityTest::AbilityRequirement(UData_AbilityRequiredInfo* requiredInfo)
{
	// ability test always return true
	return true;
}

void AAbilityTest::ActivateAbilityEffect(UData_AbilityRequiredInfo* requiredInfo)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("using test ability lv 1"));
}