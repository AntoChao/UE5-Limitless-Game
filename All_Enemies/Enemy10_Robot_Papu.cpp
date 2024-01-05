// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy10_Robot_Papu.h"
#include "Engine/EngineTypes.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "../components/HealthComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"

#include "Enemy30_AttackDrone.h"
#include "../meshes/Weapon_Laser.h"
#include "../meshes/Weapon_Gem.h"

#include "../Main.h"

// Sets default values
AEnemy10_Robot_Papu::AEnemy10_Robot_Papu() {
}

// BasicAttack
// notifier in animation
void AEnemy10_Robot_Papu::SpawnGem() {

	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	const FTransform orientation_socket_6 = Body->GetSocketTransform(Hand_Diamond_Socket, ERelativeTransformSpace::RTS_World);

	if (IsValid(MainPlayerTarget)) {
		Weapon_Gem1 = GetWorld()->SpawnActor<AWeapon_Gem>(GemClass,
			orientation_socket_6, ActorSpawnParams);
		if (IsValid(Weapon_Gem1)) {		
			Weapon_Gem1->SetTarget(MainPlayerTarget);
			Weapon_Gem1->SetEnemyController(EnemyController);
			Weapon_Gem1->SetDamage(EnemyBaseDamage);
			Weapon_Gem1->SetbNormalFire(1000.0f, true);
		}
	}
}


/* Ability 1
* Spawn 4 Attack Drone, each Drone can fire 8 missiles with each one deal 5 damage.
*/
void AEnemy10_Robot_Papu::SpawnAttackDrones() {
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	 
	const FTransform orientation_socket_1 = Body->GetSocketTransform(Drone1_Socket, ERelativeTransformSpace::RTS_World);
	const FTransform orientation_socket_2 = Body->GetSocketTransform(Drone2_Socket, ERelativeTransformSpace::RTS_World);
	const FTransform orientation_socket_3 = Body->GetSocketTransform(Drone3_Socket, ERelativeTransformSpace::RTS_World);
	const FTransform orientation_socket_4 = Body->GetSocketTransform(Drone4_Socket, ERelativeTransformSpace::RTS_World);

	// the papu does not recognize the drones, he just spawn them and leave them along
	GetWorld()->SpawnActor<AEnemy30_AttackDrone>(AttackDroneClass,
		orientation_socket_1, ActorSpawnParams);

	GetWorld()->SpawnActor<AEnemy30_AttackDrone>(AttackDroneClass,
		orientation_socket_2, ActorSpawnParams);

	GetWorld()->SpawnActor<AEnemy30_AttackDrone>(AttackDroneClass,
		orientation_socket_3, ActorSpawnParams);

	GetWorld()->SpawnActor<AEnemy30_AttackDrone>(AttackDroneClass,
		orientation_socket_4, ActorSpawnParams);
}

// Ability 2 -> latent attack -> OP Laser
// run a delay as charge, if x seg the main still in vision, fire laser
// notifier in animation
void AEnemy10_Robot_Papu::SpawnLaser() {
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	const FTransform orientation_socket_5 = Body->GetSocketTransform(Head_Laser_Socket, ERelativeTransformSpace::RTS_World);

	if (IsValid(MainPlayerTarget)) {
		Weapon_Laser = GetWorld()->SpawnActor<AWeapon_Laser>(LaserClass,
			orientation_socket_5, ActorSpawnParams);
		if (IsValid(Weapon_Laser)) {	
			Weapon_Laser->SetTarget(MainPlayerTarget);
			Weapon_Laser->SetEnemyController(EnemyController);
			Weapon_Laser->SetDamage(EnemyBaseDamage);
			Weapon_Laser->SetbNormalFire(2000.0f, true);
		}
	}
}