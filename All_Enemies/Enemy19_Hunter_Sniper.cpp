// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy19_Hunter_Sniper.h"
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
AEnemy19_Hunter_Sniper::AEnemy19_Hunter_Sniper()
{

}

// Called when the game starts or when spawned
void AEnemy19_Hunter_Sniper::BeginPlay()
{
	Super::BeginPlay();

	SpawnSniperInHand();
}

void AEnemy19_Hunter_Sniper::CustomTickFunction() {
	Super::CustomTickFunction();

	UpdateSocketsInfo();
}

void AEnemy19_Hunter_Sniper::SpawnSniperInHand()
{
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	// take careful if it is get mesh or BODY skeleton
	FTransform LeftHandTrans = Body->GetSocketTransform(Enemy_LeftHand_Socket);

	if (Weapon_SniperRifleClass) {
		Weapon_SniperRifle = GetWorld()->SpawnActor<AWeapon_SniperRifle>(Weapon_SniperRifleClass, LeftHandTrans, ActorSpawnParams);

		if (Weapon_SniperRifle != nullptr) {
			Weapon_SniperRifle->AttachToComponent(Body,
				FAttachmentTransformRules::SnapToTargetIncludingScale, Enemy_LeftHand_Socket);
		}
	}
}

void AEnemy19_Hunter_Sniper::UpdateSocketsInfo()
{
	// need to use 2k i bone in animation blueprint
	LeftHandPosition = Body->GetSocketLocation(Enemy_LeftHand_Socket);

	if (Weapon_SniperRifle) {
		WeaponFirePosition = Weapon_SniperRifle->GetMesh()->GetSocketLocation(Weapon_FirePoint_Socket);
	}
}

void AEnemy19_Hunter_Sniper::BasicAttack()
{
	// only play one the animation, but fire multiple bullets
	Super::BasicAttack();
	for (int i = 0; i < ShotTime; i++)
	{
		Fire(CalculateFireDestination());
	}
}

FVector AEnemy19_Hunter_Sniper::CalculateFireDestination()
{
	// calculate the destination
	FVector FireObjective = GetRandomNearbyLocationOfPlayer(FireOffset);
	FVector FireDirection = (FireObjective - GetActorLocation()).GetSafeNormal();

	FVector FinalDestination = GetActorLocation() + FireDirection * 500.0f;

	return FinalDestination;
}

void AEnemy19_Hunter_Sniper::Fire(FVector Destination)
{
	// Spawn bullet
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	const FTransform FireTrans = Weapon_SniperRifle->GetMesh()->GetSocketTransform(Weapon_FirePoint_Socket, ERelativeTransformSpace::RTS_World);

	AWeapon_Bullet* ABullet = GetWorld()->SpawnActor<AWeapon_Bullet>(Weapon_BulletClass,
		FireTrans, ActorSpawnParams);
	ABullet->SetTargetLocation(Destination);
	ABullet->SetEnemyController(EnemyController);
	ABullet->SetDamage(EnemyBaseDamage);
	ABullet->SetbNormalFire(3000.0f, true);

	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, TEXT("Spawning Pistol Bullet"));
}

// Throw smoke
void AEnemy19_Hunter_Sniper::Ability1()
{
	Super::Ability1();
	SpawnSmokeNiagara();
}