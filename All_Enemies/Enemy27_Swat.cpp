// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy27_Swat.h"
#include "Engine/EngineTypes.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "../components/HealthComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"
#include "../meshes/Weapon_SniperRifle.h"
#include "../meshes/Weapon_Bullet.h"
#include "../Main.h"

/*

*/
// Sets default values
AEnemy27_Swat::AEnemy27_Swat()
{

}

// Called when the game starts or when spawned
void AEnemy27_Swat::BeginPlay()
{
	Super::BeginPlay();

}

void AEnemy27_Swat::SpawnRifleInHand() {

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

void AEnemy27_Swat::UpdateSocketsInfo() {

	// need to use 2k i bone in animation blueprint
	LeftHandPosition = Body->GetSocketLocation(Enemy_LeftHand_Socket);
	WeaponFirePosition = Weapon_SniperRifle->GetMesh()->GetSocketLocation(Weapon_FirePoint_Socket);
}


void AEnemy27_Swat::BasicAttack() {

	// only play one the animation, but fire multiple bullets
	Super::BasicAttack();

	for (int i = 0; i < ShotTime; i++)
	{
		Fire(CalculateFireDestination());
	}
}

FVector AEnemy27_Swat::CalculateFireDestination() {

	// calculate the destination
	FVector FireObjective = GetRandomNearbyLocationOfPlayer(FireOffset);
	FVector FireDirection = (FireObjective - GetActorLocation()).GetSafeNormal();

	FVector FinalDestination = SelfPosition + FireDirection * 500.0f;

	return FinalDestination;
}

void AEnemy27_Swat::Fire(FVector Destination) {

	// Spawn bullet
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FTransform FireTrans = Weapon_SniperRifle->GetMesh()->GetSocketTransform(Weapon_FirePoint_Socket, ERelativeTransformSpace::RTS_World);

	AWeapon_Bullet* ABullet = GetWorld()->SpawnActor<AWeapon_Bullet>(Weapon_BulletClass,
		FireTrans, ActorSpawnParams);
	ABullet->SetTargetLocation(Destination);
	ABullet->SetEnemyController(EnemyController);
	ABullet->SetDamage(EnemyBaseDamage);
	ABullet->SetbNormalFire(2000.0f, true);

	SpawnFireNiagara();
}

void AEnemy27_Swat::Ability1()
{
	Super::Ability1();
}