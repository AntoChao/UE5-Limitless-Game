// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy25_Sandworn.h"
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
AEnemy25_Sandworn::AEnemy25_Sandworn()
{

}

// Called when the game starts or when spawned
void AEnemy25_Sandworn::BeginPlay()
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

void AEnemy25_Sandworn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemy25_Sandworn::CustomTickFunction()
{
	if (IsAbleToUseBasicAttack())
	{
		BasicAttack();
	}
}

void AEnemy25_Sandworn::BasicAttack()
{
	// only play one the animation, but fire multiple bullets
	Super::BasicAttack();

}

void AEnemy25_Sandworn::SpawnSandBullet() {

	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	const FTransform FireTrans = Body->GetSocketTransform(FirePoint_Socket, ERelativeTransformSpace::RTS_World);

	AWeapon_Bullet* ABullet = GetWorld()->SpawnActor<AWeapon_Bullet>(Weapon_BulletClass,
		FireTrans, ActorSpawnParams);
	if (IsValid(ABullet)) {
		ABullet->SetTarget(MainPlayerTarget);
		ABullet->SetEnemyController(EnemyController);
		ABullet->SetDamage(EnemyBaseDamage);
		ABullet->SetbNormalFire(3000.0f, true);

	}
	
}