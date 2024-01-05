// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy30_AttackDrone.h"
#include "Engine/EngineTypes.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "../components/HealthComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"
#include "../meshes/Weapon_Missile.h"
#include "../Main.h"


// Sets default values
AEnemy30_AttackDrone::AEnemy30_AttackDrone()
{
}

// Called when the game starts or when spawned
void AEnemy30_AttackDrone::BeginPlay()
{
	Super::BeginPlay();
}

/* BasicAttack
* fire 8 missiles
*/
void AEnemy30_AttackDrone::SpawnMissiles()
{
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	// const 
	FTransform orientation_socket_1 = Body->GetSocketTransform(Mossile_N1, ERelativeTransformSpace::RTS_World);
	FTransform orientation_socket_2 = Body->GetSocketTransform(Mossile_N2, ERelativeTransformSpace::RTS_World);
	FTransform orientation_socket_3 = Body->GetSocketTransform(Mossile_N3, ERelativeTransformSpace::RTS_World);
	FTransform orientation_socket_4 = Body->GetSocketTransform(Mossile_N4, ERelativeTransformSpace::RTS_World);
	FTransform orientation_socket_5 = Body->GetSocketTransform(Mossile_N5, ERelativeTransformSpace::RTS_World);
	FTransform orientation_socket_6 = Body->GetSocketTransform(Mossile_N6, ERelativeTransformSpace::RTS_World);
	FTransform orientation_socket_7 = Body->GetSocketTransform(Mossile_N7, ERelativeTransformSpace::RTS_World);
	FTransform orientation_socket_8 = Body->GetSocketTransform(Mossile_N8, ERelativeTransformSpace::RTS_World);

	// only spawn of the missiles are expired
	if (orientation_socket_1.IsValid() && IsValid(MainPlayerTarget)) {
		class AWeapon_Missile* Missile1 = GetWorld()->SpawnActor<AWeapon_Missile>(Weapon_MissileClass,
			orientation_socket_1, ActorSpawnParams);
		if (IsValid(Missile1)) {
			// Missile1->SetLocations(orientation_socket_1.GetTranslation(), MainPosition, MainPlayerTarget);
			Missile1->SetTarget(MainPlayerTarget);
			Missile1->SetEnemyController(EnemyController);
			Missile1->SetDamage(EnemyBaseDamage);
			Missile1->SetbStartingFire(600.0f, true);
		}
	}
	if (orientation_socket_2.IsValid() && IsValid(MainPlayerTarget)) {
		class AWeapon_Missile* Missile2 = GetWorld()->SpawnActor<AWeapon_Missile>(Weapon_MissileClass,
			orientation_socket_2, ActorSpawnParams);
		if (IsValid(Missile2)) {
			Missile2->SetTarget(MainPlayerTarget);
			Missile2->SetEnemyController(EnemyController);
			Missile2->SetDamage(EnemyBaseDamage);
			Missile2->SetbStartingFire(600.0f, true);
		}
	}

	if (orientation_socket_3.IsValid() && IsValid(MainPlayerTarget)) {
		class AWeapon_Missile* Missile3 = GetWorld()->SpawnActor<AWeapon_Missile>(Weapon_MissileClass,
			orientation_socket_3, ActorSpawnParams);
		if (IsValid(Missile3)) {
			Missile3->SetTarget(MainPlayerTarget);
			Missile3->SetEnemyController(EnemyController);
			Missile3->SetDamage(EnemyBaseDamage);
			Missile3->SetbStartingFire(600.0f, true);
		}
	}
	if (orientation_socket_4.IsValid() && IsValid(MainPlayerTarget)) {
		class AWeapon_Missile* Missile4 = GetWorld()->SpawnActor<AWeapon_Missile>(Weapon_MissileClass,
			orientation_socket_4, ActorSpawnParams);
		if (IsValid(Missile4)) {
			Missile4->SetTarget(MainPlayerTarget);
			Missile4->SetEnemyController(EnemyController);
			Missile4->SetDamage(EnemyBaseDamage);
			Missile4->SetbStartingFire(600.0f, true);
		}
	}
	if (orientation_socket_5.IsValid() && IsValid(MainPlayerTarget)) {
		class AWeapon_Missile* Missile5 = GetWorld()->SpawnActor<AWeapon_Missile>(Weapon_MissileClass,
			orientation_socket_5, ActorSpawnParams);
		if (IsValid(Missile5)) {
			Missile5->SetTarget(MainPlayerTarget);
			Missile5->SetEnemyController(EnemyController);
			Missile5->SetDamage(EnemyBaseDamage);
			Missile5->SetbStartingFire(600.0f, true);
		}
	}

	if (orientation_socket_6.IsValid() && IsValid(MainPlayerTarget)) {
		class AWeapon_Missile* Missile6 = GetWorld()->SpawnActor<AWeapon_Missile>(Weapon_MissileClass,
			orientation_socket_6, ActorSpawnParams);
		if (IsValid(Missile6)) {
			Missile6->SetTarget(MainPlayerTarget);
			Missile6->SetEnemyController(EnemyController);
			Missile6->SetDamage(EnemyBaseDamage);
			Missile6->SetbStartingFire(600.0f, true);
		}
	}
	if (orientation_socket_7.IsValid() && IsValid(MainPlayerTarget)) {
		class AWeapon_Missile* Missile7 = GetWorld()->SpawnActor<AWeapon_Missile>(Weapon_MissileClass,
			orientation_socket_7, ActorSpawnParams);
		if (IsValid(Missile7)) {
			Missile7->SetTarget(MainPlayerTarget);
			Missile7->SetEnemyController(EnemyController);
			Missile7->SetDamage(EnemyBaseDamage);
			Missile7->SetbStartingFire(600.0f, true);
		}
	}
	if (orientation_socket_8.IsValid() && IsValid(MainPlayerTarget)) {
		class AWeapon_Missile* Missile8 = GetWorld()->SpawnActor<AWeapon_Missile>(Weapon_MissileClass,
			orientation_socket_8, ActorSpawnParams);
		if (IsValid(Missile8)) {
			Missile8->SetTarget(MainPlayerTarget);
			Missile8->SetEnemyController(EnemyController);
			Missile8->SetDamage(EnemyBaseDamage);
			Missile8->SetbStartingFire(600.0f, true);
		}
	}
	IsUsingAbility1 = false;
}

// REDO
FVector AEnemy30_AttackDrone::GetAttackFinishedPosition() {
	FVector aux = AttackDirection * 2 + SelfPosition;
	return aux;
}

void AEnemy30_AttackDrone::ExtraDiedAction() {
	// eliminate the health bar
	RemoveHealthBar();

	// reward main
	RewardMainCharacter();
}