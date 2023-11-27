// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy31_KillerRabbit.h"
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
AEnemy31_KillerRabbit::AEnemy31_KillerRabbit()
{
}

// Called when the game starts or when spawned
void AEnemy31_KillerRabbit::BeginPlay()
{
	Super::BeginPlay();
	
	// Inicialize all values
	// TESTING
	InitCharacHealth(50.0f);
	
	SetRarity(EEnemyRarity::ENormal);

	GeneralDistance = 1500.0f;

	AbilityOneDistance = 1500.f;
	
	// GetCharacterMovement()->MaxWalkSpeed = FlySpeed;

	EnemyBaseDamage = 2.0f;

}

void AEnemy31_KillerRabbit::CustomTickFunction()
{
	Super::CustomTickFunction();

}

FVector AEnemy31_KillerRabbit::GetAttackFinishedPosition()
{
	FVector aux = AttackDirection * 2 + SelfPosition;
	//aux.Z = 105.5f;
	DrawDebugSphere
	(
		GetWorld(), aux, 10.0f, 10, FColor::Green, false, 10.0f, 2, 10.0f
	);
	return aux;
}

// Only use basic attack -> has lots of velocity...