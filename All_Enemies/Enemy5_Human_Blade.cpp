// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy5_Human_Blade.h"
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
AEnemy5_Human_Blade::AEnemy5_Human_Blade()
{
}

// Called when the game starts or when spawned
void AEnemy5_Human_Blade::BeginPlay()
{
	Super::BeginPlay();
	
	// Inicialize all values
	InitCharacHealth(100.0f);

	SetRarity(EEnemyRarity::ENormal);

	MoveSpeed = 900.0f;

	GeneralDistance = 2000.0f;

	BasicAttackDistance = 100.0f;
	AbilityOneDistance = 1000.f;

	Ability1Duration = 5.0f;

	SpawnBladeInHand();
}

void AEnemy5_Human_Blade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateSocketsInfo();
}

void AEnemy5_Human_Blade::SpawnBladeInHand()
{
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	// take careful if it is get mesh or BODY skeleton
	FTransform LeftHandTrans = Body->GetSocketTransform(Enemy_LeftHand_Socket);

	if (Weapon_BladeClass)
	{
		Weapon_Blade = GetWorld()->SpawnActor<AWeapon_Blade>(Weapon_BladeClass, LeftHandTrans, ActorSpawnParams);

		if (Weapon_Blade != nullptr)
		{
			Weapon_Blade->AttachToComponent(Body,
				FAttachmentTransformRules::SnapToTargetIncludingScale, Enemy_LeftHand_Socket);
		}
	}
}

void AEnemy5_Human_Blade::UpdateSocketsInfo()
{
	// need to use 2k i bone in animation blueprint
	LeftHandPosition = Body->GetSocketLocation(Enemy_LeftHand_Socket);
}

// Basic Attack
void AEnemy5_Human_Blade::BasicAttack()
{
	Super::BasicAttack();
	DealDamage2Overlapped();
}

// Ability
void AEnemy5_Human_Blade::Ability1()
{
	Super::Ability1();

	TPLocation = GetRandomNearbyLocationOfPlayer(BasicAttackDistance);
	SpawnTPNiagara(TPLocation);
	SetActorLocation(TPLocation);
}