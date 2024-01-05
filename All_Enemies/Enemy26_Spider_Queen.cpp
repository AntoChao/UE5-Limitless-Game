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

void AEnemy26_Spider_Queen::BasicAttackStun() {
	CollisionComp->GetOverlappingActors(OverlappedActors, AActor::StaticClass());
	for (AActor* Actor : OverlappedActors) {
		if (IsValid(Actor)) {
			AMain* Player = Cast<AMain>(Actor);
			if (IsValid(Player)) {
				Player->Immovilize(StunTime);
			}
		}
	}
}

void AEnemy26_Spider_Queen::BasicAttackDealDamage() {

	SpawnGroundHitNiagara();

	// need to set collision as around player
	DealDamage2Overlapped();
}

void AEnemy26_Spider_Queen::SpawnSpiderBullet() {

	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	const FTransform FireTrans = Body->GetSocketTransform(Weapon_FirePoint_Socket, 
		ERelativeTransformSpace::RTS_World);
	
	if (IsValid(MainPlayerTarget)) {
		AWeapon_Bullet* ABullet = GetWorld()->SpawnActor<AWeapon_Bullet>(Weapon_BulletClass,
				FireTrans, ActorSpawnParams);

		if (IsValid(ABullet)) {		
			ABullet->SetTarget(MainPlayerTarget);
			ABullet->SetEnemyController(EnemyController);
			ABullet->SetDamage(EnemyBaseDamage);
			ABullet->SetbNormalFire(3000.0f, true);
		}
	}
}