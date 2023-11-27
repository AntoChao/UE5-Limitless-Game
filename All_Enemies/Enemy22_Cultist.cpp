// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy22_Cultist.h"
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
AEnemy22_Cultist::AEnemy22_Cultist()
{

}

// Called when the game starts or when spawned
void AEnemy22_Cultist::BeginPlay()
{
	Super::BeginPlay();
	
	// Inicialize all values
	InitCharacHealth(100.0f);

	SetRarity(EEnemyRarity::ENormal);

	GeneralDistance = 2000.0f;

	BasicAttackDistance = 500.0f;
	AbilityOneDistance = 300.f;

	Ability1Duration = 1.0f;

}

void AEnemy22_Cultist::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemy22_Cultist::BasicAttack()
{
	// only play one the animation
	Super::BasicAttack();
}

// basic attack called in animation
void AEnemy22_Cultist::SpawnCultist() {
	
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FVector TargetPosition = SelfPosition + SpawnXYOffset;

	// it automatically change the random location variable
	GenerateRandomPoint(SelfPosition, TargetPosition);

	RandomLocation = RandomLocation + SpawnHeightOffset;

	DrawDebugSphere (
		GetWorld(), RandomLocation, 10.0f, 10, FColor::Yellow, false, 10.0f, 2, 10.0f
	);

	AEnemy22_Cultist* ACultist = GetWorld()->SpawnActor<AEnemy22_Cultist>(CultistClass,
		RandomLocation, GetActorRotation(), ActorSpawnParams);
}

void AEnemy22_Cultist::Ability1()
{
	Super::Ability1();

	// Suicide, no need to pass an actual controller.
	UGameplayStatics::ApplyPointDamage(this, SelfDestoyDamage,
		GetActorLocation(), EnemyHit,
		nullptr, this, nullptr);
}

void AEnemy22_Cultist::ExtraDiedAction()
{
	Super::ExtraDiedAction();

	SpawnSuicideExplotionNiagara();

	// need to set collision as around player
	DealDamage2Overlapped();
}