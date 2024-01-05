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
AEnemy24_MiniBot::AEnemy24_MiniBot() {

}

void AEnemy24_MiniBot::SpawnBasicBullet() {

	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FTransform FireTrans = Body->GetSocketTransform(FirePoint_Socket, ERelativeTransformSpace::RTS_World);

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
