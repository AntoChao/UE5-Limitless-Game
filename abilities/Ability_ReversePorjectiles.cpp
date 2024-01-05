// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability_ReversePorjectiles.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Engine/EngineTypes.h"
#include "Engine/Blueprint.h"
#include "DrawDebugHelpers.h"
#include "Math/Vector.h"
#include "../meshes/Weapon_GeneralClass.h"
#include "../meshes/Weapon_ReverseProjectile.h"
#include "../AllCharactersClass.h"
#include "../All_Enemies/EnemyClass.h"
// Sets default values
AAbility_ReversePorjectiles::AAbility_ReversePorjectiles(const class FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer) {
}

void AAbility_ReversePorjectiles::ActivateAbilityEffect(UData_AbilityRequiredInfo* requiredInfo) {
	ResetArrays();

	Weapon_ReverseProjectileClass = requiredInfo->GetPlayer()->GetReverseProjectilesClass();

	// Ability Effect -> Get all actors in x Radius and set them
	GetAllEnemiesProjectiles(requiredInfo);
	SetAllProjectiles(requiredInfo);
}

void AAbility_ReversePorjectiles::GetAllEnemiesProjectiles(UData_AbilityRequiredInfo* requiredInfo) {

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), ActorsDetected);

	for (AActor* Actor : ActorsDetected) {	
		if (IsValid(Actor)) {
			float Distance = (Actor->GetActorLocation() - requiredInfo->GetPlayerLocation()).Size();
			if (Distance <= RadiusOfDetection) {
				if (Actor->GetClass()->IsChildOf(AWeapon_GProjectileClass::StaticClass())) {
					
					AWeapon_GProjectileClass* WeaponDelta = Cast<AWeapon_GProjectileClass>(Actor);
					if (IsValid(WeaponDelta)) {
						EnemiesProjectiles.Add(WeaponDelta);
					}
				}
				else if (Actor->GetClass()->IsChildOf(AEnemyClass::StaticClass())) {

					AEnemyClass* EnemyDelta = Cast<AEnemyClass>(Actor);
					if (IsValid(EnemyDelta)) {
						EnemiesDetected.Add(EnemyDelta);
					}
				}
			}
		}
	}
}

// Set -> Destroy the original, replace it with a reverse weapon and set the stats
void AAbility_ReversePorjectiles::SetAllProjectiles(UData_AbilityRequiredInfo* requiredInfo) {
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	for (AWeapon_GProjectileClass* Projectile : EnemiesProjectiles) {
		AEnemyClass* EnemySelected = SelectARandomEnemy();
		if (IsValid(Projectile)) {
			FVector DeltaVector = Projectile->GetCollisionLocation();

			Projectile->Destroy();

			if (IsValid(EnemySelected)) {
				// replace the projectile to reverse one
				AWeapon_ReverseProjectile* DeltaProjectile = requiredInfo->GetWorldPointer()->
					SpawnActor<AWeapon_ReverseProjectile>(Weapon_ReverseProjectileClass,
						DeltaVector, FRotator(0.0f, 0.0f, 0.0f), ActorSpawnParams);

				// setting stats
				if (IsValid(DeltaProjectile)) {
					DeltaProjectile->SetTarget(EnemySelected);
					DeltaProjectile->SetMainController(requiredInfo->GetPlayer()->GetMainController());
					// CalculateDamage();
					DeltaProjectile->SetDamage(CalculateGeneralDamage(requiredInfo));
					DeltaProjectile->SetbNormalFire(1000.0f, true);
				}
			}
		}
	}
}

AEnemyClass* AAbility_ReversePorjectiles::SelectARandomEnemy() {
	// chose one of the enemy
	int AmountOfEnemiesDetected = EnemiesDetected.Num();
	if (AmountOfEnemiesDetected >= 1) {
		int Index = FMath::RandRange(0, AmountOfEnemiesDetected - 1);

		return EnemiesDetected[Index];
	}
	else {
		return nullptr;
	}
	
}

void AAbility_ReversePorjectiles::ResetArrays() {
	ActorsDetected = {};
	EnemiesProjectiles = {};
	EnemiesDetected = {};
}