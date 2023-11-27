// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy7_Human_Shotgun.h"
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
AEnemy7_Human_Shotgun::AEnemy7_Human_Shotgun()
{

}

// Called when the game starts or when spawned
void AEnemy7_Human_Shotgun::BeginPlay()
{
	Super::BeginPlay();
	
	// Inicialize all values
	InitCharacHealth(100.0f);

	SetRarity(EEnemyRarity::ENormal);

	GeneralDistance = 2000.0f;

	BasicAttackDistance = 500.0f;
	AbilityOneDistance = 300.f;

	Ability1Duration = 1.0f;

	SpawnShotgunInHand();
}

void AEnemy7_Human_Shotgun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateSocketsInfo();
}

void AEnemy7_Human_Shotgun::SpawnShotgunInHand()
{
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	// take careful if it is get mesh or BODY skeleton
	FTransform LeftHandTrans = Body->GetSocketTransform(Enemy_LeftHand_Socket);

	if (Weapon_ShotgunClass)
	{
		Weapon_Shotgun = GetWorld()->SpawnActor<AWeapon_Shotgun>(Weapon_ShotgunClass, LeftHandTrans, ActorSpawnParams);

		if (Weapon_Shotgun != nullptr)
		{
			Weapon_Shotgun->AttachToComponent(Body,
				FAttachmentTransformRules::SnapToTargetIncludingScale, Enemy_LeftHand_Socket);
		}
	}
}
void AEnemy7_Human_Shotgun::UpdateSocketsInfo()
{
	// need to use 2k i bone in animation blueprint
	LeftHandPosition = Body->GetSocketLocation(Enemy_LeftHand_Socket);
	WeaponFirePosition = Weapon_Shotgun->GetMesh()->GetSocketLocation(Weapon_FirePoint_Socket);
}

void AEnemy7_Human_Shotgun::FireBasicAttack()
{
	// only play one the animation, but fire multiple bullets
	for (int i = 0; i < ShotTime; i++)
	{
		Fire(CalculateFireDestination());
	}
}

FVector AEnemy7_Human_Shotgun::CalculateFireDestination()
{
	// calculate the destination
	FVector FireObjective = GetRandomNearbyLocationOfPlayer(FireOffset);
	FVector FireDirection = (FireObjective - GetActorLocation()).GetSafeNormal();

	FVector FinalDestination = GetActorLocation() + FireDirection * 500.0f;

	return FinalDestination;
}

void AEnemy7_Human_Shotgun::Fire(FVector Destination)
{
	// Spawn bullet
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	const FTransform FireTrans = Weapon_Shotgun->GetMesh()->GetSocketTransform(Weapon_FirePoint_Socket, ERelativeTransformSpace::RTS_World);

	AWeapon_Bullet* ABullet = GetWorld()->SpawnActor<AWeapon_Bullet>(Weapon_BulletClass,
		FireTrans, ActorSpawnParams);
	ABullet->SetTargetLocation(Destination);
	ABullet->SetEnemyController(EnemyController);
	ABullet->SetDamage(EnemyBaseDamage);
	ABullet->SetbNormalFire(2000.0f, true);

	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, TEXT("Spawning Shotgun Bullet"));
}
