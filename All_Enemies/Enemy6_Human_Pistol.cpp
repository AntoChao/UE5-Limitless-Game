// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy6_Human_Pistol.h"
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
AEnemy6_Human_Pistol::AEnemy6_Human_Pistol()
{
}

// Called when the game starts or when spawned
void AEnemy6_Human_Pistol::BeginPlay()
{
	Super::BeginPlay();
	
	// Inicialize all values
	InitCharacHealth(100.0f);
	
	SetRarity(EEnemyRarity::ENormal);

	GeneralDistance = 2000.0f;

	BasicAttackDistance = 1200.0f;
	AbilityOneDistance = 1000.f;
	
	Ability1Duration = 1.0f;
	
	SpawnPistolInHand();
}

void AEnemy6_Human_Pistol::CustomTickFunction()
{
	Super::CustomTickFunction();

	UpdateSocketsInfo();
}

void AEnemy6_Human_Pistol::SpawnPistolInHand()
{
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	// take careful if it is get mesh or BODY skeleton
	FTransform LeftHandTrans = Body->GetSocketTransform(Enemy_LeftHand_Socket);

	if (Weapon_PistolClass)
	{
		Weapon_Pistol = GetWorld()->SpawnActor<AWeapon_Pistol>(Weapon_PistolClass, LeftHandTrans, ActorSpawnParams);

		if (Weapon_Pistol != nullptr)
		{
			Weapon_Pistol->AttachToComponent(Body,
				FAttachmentTransformRules::SnapToTargetIncludingScale, Enemy_LeftHand_Socket);
		}
	}
}

void AEnemy6_Human_Pistol::UpdateSocketsInfo()
{
	// need to use 2k i bone in animation blueprint
	LeftHandPosition = Body->GetSocketLocation(Enemy_LeftHand_Socket);
	WeaponFirePosition = Weapon_Pistol->GetMesh()->GetSocketLocation(Weapon_FirePoint_Socket);
}

void AEnemy6_Human_Pistol::BasicAttack()
{
	Super::BasicAttack();
	Fire(CalculateFireDestination());
}

FVector AEnemy6_Human_Pistol::CalculateFireDestination()
{
	// calculate the destination
	FVector FireObjective = GetRandomNearbyLocationOfPlayer(FireOffset);
	FVector FireDirection = (FireObjective - GetActorLocation()).GetSafeNormal();

	FVector FinalDestination = GetActorLocation() + FireDirection * 1000.0f;

	return FinalDestination;
}

void AEnemy6_Human_Pistol::Fire(FVector Destination)
{
	// Spawn bullet
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	const FTransform FireTrans = Weapon_Pistol->GetMesh()->GetSocketTransform(Weapon_FirePoint_Socket, ERelativeTransformSpace::RTS_World);

	AWeapon_Bullet* ABullet = GetWorld()->SpawnActor<AWeapon_Bullet>(Weapon_BulletClass,
		FireTrans, ActorSpawnParams);
	ABullet->SetTargetLocation(Destination);
	ABullet->SetEnemyController(EnemyController);
	ABullet->SetDamage(EnemyBaseDamage);
	ABullet->SetbNormalFire(2000.0f, true);

	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, TEXT("Spawning Pistol Bullet"));
}

void AEnemy6_Human_Pistol::Ability1()
{
	Super::Ability1();
	// fast shotting pistol a few times
	for (int i = 0; i < ShotTime; i++)
	{
		PlayAnimAbilityOne();
		Fire(CalculateFireDestination());
	}
}