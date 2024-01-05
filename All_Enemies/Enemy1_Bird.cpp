// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy1_Bird.h"
#include "Engine/EngineTypes.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "../components/HealthComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"
#include "../meshes/Enemy1_Bird_WindSlash.h"
#include "../Main.h"

/*

*/
// Sets default values
AEnemy1_Bird::AEnemy1_Bird() {

}

/*
* Dash Attack, should create a collition or enable the collision around bird, and deal damage
*/
void AEnemy1_Bird::BasicAttack() {
	Super::BasicAttack();
	UpdateExtraSpeed(2000.0f);
}

FVector AEnemy1_Bird::GetAttackFinishedPosition() {
	FVector aux = AttackDirection * 2 + SelfPosition;

	return aux;
}

void AEnemy1_Bird::BasicAttackFinished() {
	Super::BasicAttackFinished();
	ResetExtraSpeed();
}

void AEnemy1_Bird::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp,
	class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (IsAttacking) {
		if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr)) {
			// if (OtherActor->GetClass()->IsChildOf(AAllCharactersClass::StaticClass()))
			if (OtherActor->IsA(AMain::StaticClass())) {
				// Apply damage
				ApplyDamageToMain(EnemyBaseDamage);
			}
		}
	}
}

void AEnemy1_Bird::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp,
	class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex) {
	// nothing
}

void AEnemy1_Bird::Ability1() {
	Super::Ability1();
	
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	const FTransform orientation_socket_1 = Body->GetSocketTransform(Wind_Slash_Socket_1, ERelativeTransformSpace::RTS_World);
	const FTransform orientation_socket_2 = Body->GetSocketTransform(Wind_Slash_Socket_2, ERelativeTransformSpace::RTS_World);

	WindSlash1 = GetWorld()->SpawnActor<AEnemy1_Bird_WindSlash>(WindSlashClass,
		orientation_socket_1, ActorSpawnParams);
	if (IsValid(WindSlash1)) {
		WindSlash1->SetTarget(MainPlayerTarget);
		WindSlash1->SetEnemyController(EnemyController);
		WindSlash1->SetDamage(EnemyBaseDamage);
		WindSlash1->SetbNormalFire(1500.0f, true);

	}
	
	WindSlash2 = GetWorld()->SpawnActor<AEnemy1_Bird_WindSlash>(WindSlashClass,
		orientation_socket_2, ActorSpawnParams);
	if (IsValid(WindSlash2)) {
		WindSlash2->SetTarget(MainPlayerTarget);
		WindSlash2->SetEnemyController(EnemyController);
		WindSlash2->SetDamage(EnemyBaseDamage);
		WindSlash2->SetbNormalFire(1500.0f, true);
	}
}