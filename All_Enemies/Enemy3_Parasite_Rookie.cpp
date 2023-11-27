// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy3_Parasite_Rookie.h"
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
AEnemy3_Parasite_Rookie::AEnemy3_Parasite_Rookie()
{
}

// Called when the game starts or when spawned
void AEnemy3_Parasite_Rookie::BeginPlay()
{
	Super::BeginPlay();
	
	// Inicialize all values
	InitCharacHealth(100.0f);
	
	SetRarity(EEnemyRarity::ENormal);

	GeneralDistance = 2000.0f;

	BasicAttackDistance = 100.0f;
	AbilityOneDistance = 1000.f;

	Ability1Duration = 1.0f;

}

void AEnemy3_Parasite_Rookie::CustomTickFunction()
{
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	Super::CustomTickFunction();
	// maybe spawn venom gas each custom tick 
	GetWorld()->SpawnActor<AEnemy2_Parasite_VenomGas>(VenomGasClass,
		SelfPosition, GetActorRotation(), ActorSpawnParams);
}

void AEnemy3_Parasite_Rookie::BasicAttack()
{
	Super::BasicAttack();
	DealDamage2Overlapped();
}

void AEnemy3_Parasite_Rookie::Ability1()
{
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	// may cause error by being the same spot and collition stuff
	for (int i = 0; i < AmountOfBaby2Spawn; i++)
	{
		GetWorld()->SpawnActor<AEnemy2_Parasite_Baby>(Parasite_BabyClass,
			SelfPosition, GetActorRotation(), ActorSpawnParams);
	}
}

void AEnemy3_Parasite_Rookie::ExtraDiedAction()
{
	Super::ExtraDiedAction();
	Ability1();
}