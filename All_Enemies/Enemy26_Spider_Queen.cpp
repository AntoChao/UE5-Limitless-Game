// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy26_Spider_Queen.h"
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
AEnemy26_Spider_Queen::AEnemy26_Spider_Queen() {

}

// Called when the game starts or when spawned
void AEnemy26_Spider_Queen::BeginPlay() {
	Super::BeginPlay();
	
	// Inicialize all values
	InitCharacHealth(100.0f);

	SetRarity(EEnemyRarity::ENormal);

	GeneralDistance = 2000.0f;

	BasicAttackDistance = 500.0f;
	AbilityOneDistance = 300.f;

	Ability1Duration = 1.0f;

}

void AEnemy26_Spider_Queen::BasicAttack() {
	// only play one the animation

	IsAttacking = true;

	float Distance = AttackDirection.Size();

	if (Distance < AttackDistance)
		IsInDistance = true;
	else
		IsInDistance = false;

	PlayAnimBasicAttack();
}

void AEnemy26_Spider_Queen::BasicAttackFinished() {
	Super::BasicAttackFinished();

	SpawnGroundHitNiagara();

	// need to set collision as around player
	DealDamage2Overlapped();
}

void AEnemy26_Spider_Queen::PlayAnimBasicAttack() {
	UAnimInstance* AnimInstance = Body->GetAnimInstance();

	if (AnimInstance) {
		if (IsInDistance) {
			if (IsValid(AnimMontage_JumpStandAttack)){
				AnimInstance->Montage_Play(AnimMontage_JumpStandAttack, PlayRate);
			}
		}
		else {
			if (IsValid(AnimMontage_JumpLaunchAttack)) {
				AnimInstance->Montage_Play(AnimMontage_JumpLaunchAttack, PlayRate);
			}
		}

		// Bind the OnMontageEnded event to a custom function
		AnimInstance->OnMontageEnded.AddDynamic(this, &AEnemy26_Spider_Queen::OnMontageBasicAttackEnded);
		
	}
}

void AEnemy26_Spider_Queen::Ability1()
{
	Super::Ability1();
}

void AEnemy26_Spider_Queen::SpawnSpiderBullet() {

	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	const FTransform FireTrans = Body->GetSocketTransform(Weapon_FirePoint_Socket, ERelativeTransformSpace::RTS_World);

	
		AWeapon_Bullet* ABullet = GetWorld()->SpawnActor<AWeapon_Bullet>(Weapon_BulletClass,
			FireTrans, ActorSpawnParams);
	if (IsValid(ABullet)) {
		ABullet->SetTarget(MainPlayerTarget);
		ABullet->SetEnemyController(EnemyController);
		ABullet->SetDamage(EnemyBaseDamage);
		ABullet->SetbNormalFire(3000.0f, true);
	}
	
}