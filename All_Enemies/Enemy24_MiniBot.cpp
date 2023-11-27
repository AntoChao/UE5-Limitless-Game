// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy24_MiniBot.h"
#include "Engine/EngineTypes.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "../components/HealthComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"
#include "../meshes/Weapon_Bullet.h"
#include "../Main.h"

/*

*/
// Sets default values
AEnemy24_MiniBot::AEnemy24_MiniBot()
{

}

// Called when the game starts or when spawned
void AEnemy24_MiniBot::BeginPlay()
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

void AEnemy24_MiniBot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemy24_MiniBot::CustomTickFunction()
{
	if (IsAbleToUseBasicAttack())
	{
		BasicAttack();
	}
}

void AEnemy24_MiniBot::BasicAttack()
{
	// only play one the animation, but fire multiple bullets
	Super::BasicAttack();
}

void AEnemy24_MiniBot::SpawnBasicBullet() {

	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FTransform FireTrans = Body->GetSocketTransform(FirePoint_Socket, ERelativeTransformSpace::RTS_World);

	AWeapon_Bullet* ABullet = GetWorld()->SpawnActor<AWeapon_Bullet>(Weapon_BulletClass,
		FireTrans, ActorSpawnParams);
	
	if (IsValid(ABullet)) {
		ABullet->SetTarget(MainPlayerTarget);
		ABullet->SetEnemyController(EnemyController);
		ABullet->SetDamage(EnemyBaseDamage);
		ABullet->SetbNormalFire(3000.0f, true);
	}
	
}

void AEnemy24_MiniBot::Ability1()
{
	Super::Ability1();
}