// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicEnemy.h"
#include "Engine/EngineTypes.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "../components/HealthComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"
#include "../Main.h"

// Sets default values
ABasicEnemy::ABasicEnemy()
{
	// Set size for collision capsule
	// GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
}

// Called when the game starts or when spawned
void ABasicEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	// Inicialize all values
	InitCharacHealth(100.0f);

	SetRarity(EEnemyRarity::ENormal);

}

bool ABasicEnemy::IsAbleToUseAbility1()
{
	FString miau = FString::SanitizeFloat(AttackDirection.Size());
	GEngine->AddOnScreenDebugMessage(-1, 2.0, FColor::Red, *miau);

	return AttackDirection.Size() <= AbilityOneDistance;

}
bool ABasicEnemy::IsAbleToUseAbility2()
{
	return AttackDirection.Size() <= AbilityTwoDistance;
}

void ABasicEnemy::Ability1()
{
	Super::Ability1();

	ApplyDamageToMain(5.0f);
}

void ABasicEnemy::Ability2()
{
	Super::Ability2();
	ApplyDamageToMain(10.0f);
}
