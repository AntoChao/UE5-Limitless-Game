// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy28_Wasp.h"
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
AEnemy28_Wasp::AEnemy28_Wasp()
{

}

// Called when the game starts or when spawned
void AEnemy28_Wasp::BeginPlay()
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

void AEnemy28_Wasp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemy28_Wasp::CustomTickFunction(){
	Super::CustomTickFunction();

	TArray<AActor*> OverlappingActors;
	CollisionComp->GetOverlappingActors(OverlappingActors, AActor::StaticClass());
	for (AActor* OverlappingActor : OverlappingActors)
	{
		if (MainPlayerTarget == OverlappingActor) {
			UGameplayStatics::ApplyPointDamage(MainPlayerTarget, EnemyBaseDamage,
				GetActorLocation(), EnemyHit,
				nullptr, this, nullptr);
		}
	}
}
void AEnemy28_Wasp::BasicAttack()
{
	// only play one the animation
	Super::BasicAttack();

}

void AEnemy28_Wasp::Ability1()
{
	Super::Ability1();
}






