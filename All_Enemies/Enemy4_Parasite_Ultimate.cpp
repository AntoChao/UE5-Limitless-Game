// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy4_Parasite_Ultimate.h"
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

/*

*/
// Sets default values
AEnemy4_Parasite_Ultimate::AEnemy4_Parasite_Ultimate()
{
}

// Called when the game starts or when spawned
void AEnemy4_Parasite_Ultimate::BeginPlay()
{
	Super::BeginPlay();

	// Inicialize all values
	InitCharacHealth(100.0f);

	SetRarity(EEnemyRarity::ENormal);

	GeneralDistance = 2000.0f;

	BasicAttackDistance = 200.0f;
	AbilityOneDistance = 1000.f;
	AbilityTwoDistance = 1000.f;

	Ability1Duration = 5.0f;
	Ability2Duration = 1.0f;

	IsChargingBeam = false;
	IsRelesingBeam = false;
	BeamChargingDuration = 3.0f;
	BeamReleasingDuration = 10.0f;
}

void AEnemy4_Parasite_Ultimate::CustomTickFunction()
{
	Super::CustomTickFunction();
	if (IsChargingBeam)
	{
		FRotator AttackRotation = AttackDirection.Rotation();
		SetActorRotation(AttackRotation);

		DrawDebugLine(GetWorld(), MainPosition, SelfPosition, FColor::Green, false, 1, 0, 1);
	}

	if (IsRelesingBeam)
	{
		DrawDebugLine(GetWorld(), MainPosition, SelfPosition, FColor::Red, false, 1, 0, 1);
		ApplyDamageToMain(1.0f);
	}
}

void AEnemy4_Parasite_Ultimate::BasicAttack()
{
	Super::BasicAttack();
	DealDamage2Overlapped();
}

// Charge for 3 seconds, if the enemy is still in vision, shot a lacer
// A Latent ability
void AEnemy4_Parasite_Ultimate::Ability1()
{
	Super::Ability1();

	// GetCharacterMovement()->MaxWalkSpeed = 0.0f;
	IsChargingBeam = true;
}

/*
A beam is just a generative niagara between enemy and 
character, character receive damage
*/
void AEnemy4_Parasite_Ultimate::ReleaseBeam()
{
	IsChargingBeam = false;
	IsRelesingBeam = true;
}

void AEnemy4_Parasite_Ultimate::BeamFinished()
{
	IsRelesingBeam = false;
	IsUsingAbility1 = false;
	// GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;
}

// Ability 2 should be deal radial damage, move to is logic of moveto node
void AEnemy4_Parasite_Ultimate::Ability2()
{
	Super::Ability2();
	
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Using Ability 2"));
}