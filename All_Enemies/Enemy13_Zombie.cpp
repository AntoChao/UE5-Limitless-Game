// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy13_Zombie.h"
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
#include "../meshes/Weapon_GeneralClass.h"
#include "../meshes/Weapon_Shotgun.h"

// Sets default values
AEnemy13_Zombie::AEnemy13_Zombie()
{
}

// Called when the game starts or when spawned
void AEnemy13_Zombie::BeginPlay()
{
	Super::BeginPlay();
	
	// Inicialize all values
	InitCharacHealth(100.0f);
	
	SetRarity(EEnemyRarity::ENormal);

	GeneralDistance = 1000.0f;

	IsJumping = false;
	WalkSpeed = 600.0f;
	JumpSpeed = 3000.0f;

	AbilityOneDistance = 1000.f;
	AbilityTwoDistance = 1000.f;

	Ability1Duration = 1.0f;
	Ability2Duration = 1.0f;

}


bool AEnemy13_Zombie::IsAbleToUseAbility1()
{
	return AttackDirection.Size() <= AbilityOneDistance;
}
bool AEnemy13_Zombie::IsAbleToUseAbility2()
{
	return AttackDirection.Size() <= AbilityTwoDistance;
}

// Melee Attack
void AEnemy13_Zombie::BasicAttack()
{
	Super::BasicAttack();
	// deal damage -> in reality should be part of animation
	DealDamage2Overlapped();
}

/*
* jumpmelee attack
* 1: jump to the place -> move really fast and get close to the place, anim montage
* 2: create a collision box, if the enemy in place -> deal damage
*/
// Ability 1 just correspond the jump -> max speed, the position is just moveto node
void AEnemy13_Zombie::Ability1()
{
	Super::Ability1();
	IsJumping = true;
	// speed boost
}

void AEnemy13_Zombie::Ability1Finished()
{
	Super::Ability1Finished();
	IsJumping = false;
}

// Ability 2
void AEnemy13_Zombie::Ability2()
{
	Super::Ability2();
}
