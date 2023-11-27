// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy2_Parasite_Baby.h"
#include "Engine/EngineTypes.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "../components/HealthComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"
#include "Enemy2_Parasite_VenomGas.h"
#include "../Main.h"

/*

*/
// Sets default values
AEnemy2_Parasite_Baby::AEnemy2_Parasite_Baby()
{
}

// Called when the game starts or when spawned
void AEnemy2_Parasite_Baby::BeginPlay()
{
	Super::BeginPlay();
	
	// Inicialize all values
	InitCharacHealth(100.0f);
	
	SetRarity(EEnemyRarity::ENormal);

	GeneralDistance = 100.0f;

	BasicAttackDistance = 10.0f;
}

void AEnemy2_Parasite_Baby::BasicAttack()
{
	Super::BasicAttack();
	DealDamage2Overlapped();
}

// only Activate when the bicho died, it is added at extra dead function
void AEnemy2_Parasite_Baby::Ability1()
{
	Super::Ability1();
	
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	VenomGas = GetWorld()->SpawnActor<AEnemy2_Parasite_VenomGas>(VenomGasClass,
		SelfPosition, GetActorRotation(), ActorSpawnParams);
}

void AEnemy2_Parasite_Baby::ExtraDiedAction()
{
	Ability1();
}