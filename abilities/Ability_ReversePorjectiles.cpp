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
	:Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAbility_ReversePorjectiles::BeginPlay()
{
	Super::BeginPlay();
}

bool AAbility_ReversePorjectiles::AbilityRequirement(UData_AbilityRequiredInfo* requiredInfo)
{
	if (requiredInfo->GetPlayerFrenzy() >= FrenzyCost->GetFrenzy())
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*  ActivateAbilityEffect has 3 process
*	Customize ability stats
*	Do the effect
*	Calculate feedback in order to return -> override all calculution base on ability
*/
void AAbility_ReversePorjectiles::ActivateAbilityEffect(UData_AbilityRequiredInfo* requiredInfo)
{
	ResetArrays();

	// Set the TSubClassArray
	Weapon_ReverseProjectileClass = requiredInfo->GetPlayer()->GetReverseProjectilesClass();

	// Ability Effect -> Get all actors in x Radius and set them
	GetAllEnemiesProjectiles(requiredInfo);
	SetAllProjectiles(requiredInfo);

	// Calculate the feedback -> override all calculation -> the calculation is done after receive the decision
	// freCost, freReward, cocost, coReward, moveSpeedRew, Xp
}

void AAbility_ReversePorjectiles::GetAllEnemiesProjectiles(UData_AbilityRequiredInfo* requiredInfo)
{
	requiredInfo->GetPlayer()->SetNewDetectionAreaRadius(RadiusOfDetection);
	float RadiusDelta = requiredInfo->GetPlayer()->GetNewDetectionAreaRadius();
	
	for (AActor* Actor : requiredInfo->GetPlayer()->GetAllDetectedActors())
	{
		
		requiredInfo->GetPlayer()->ResetDetectionAreaRadius();

		if (IsValid(Actor))
		{
			float Distance = (Actor->GetActorLocation() - requiredInfo->GetPlayerLocation()).Size();
			// check if the weapon is "valid" and owned by enemies

			if (Actor->GetClass()->IsChildOf(AWeapon_GeneralClass::StaticClass()))
			{
				DrawDebugSphere
				(
					GetWorld(), Actor->GetActorLocation(), 10.0f, 10, FColor::Red, false, 10.0f, 2, 1.0f
				);

				if (Distance <= RadiusDelta)
				{
					AWeapon_GProjectileClass* WeaponDelta = Cast<AWeapon_GProjectileClass>(Actor);
					if (IsValid(WeaponDelta))
					{
						EnemiesProjectiles.Add(WeaponDelta);
					}
				}
			}
			else if (Actor->GetClass()->IsChildOf(AEnemyClass::StaticClass()))
			{
				GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, TEXT("04"));
				if (Distance <= RadiusDelta)
				{
					GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, TEXT("05"));
					AEnemyClass* EnemyDelta = Cast<AEnemyClass>(Actor);
					EnemiesDetected.Add(EnemyDelta);
				}
				else
				{
					GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, TEXT("06"));
				}
			}
		}
		
	}
}

// Set -> Destroy the original, replace it with a reverse weapon and set the stats
void AAbility_ReversePorjectiles::SetAllProjectiles(UData_AbilityRequiredInfo* requiredInfo)
{
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AEnemyClass* EnemySelected = SelectARandomEnemy();

	for (AWeapon_GProjectileClass* Projectile : EnemiesProjectiles)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, TEXT("1"));

		if (IsValid(Projectile))
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, TEXT("2"));

			FVector DeltaVector = Projectile->GetCollisionLocation();

			Projectile->Destroy();

			if (IsValid(EnemySelected))
			{
				GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, TEXT("3"));

				// replace the projectile to reverse one
				AWeapon_ReverseProjectile* DeltaProjectile = requiredInfo->GetWorldPointer()->
					SpawnActor<AWeapon_ReverseProjectile>(Weapon_ReverseProjectileClass,
						DeltaVector, FRotator(0.0f, 0.0f, 0.0f), ActorSpawnParams);

				// setting stats
				DeltaProjectile->SetTarget(EnemySelected);
				DeltaProjectile->SetMainController(requiredInfo->GetPlayer()->GetMainController());
				// CalculateDamage();
				DeltaProjectile->SetDamage(CalculateGeneralDamage(requiredInfo));
				DeltaProjectile->SetbNormalFire(1000.0f, true);
				GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, TEXT("Reverse Porjectiles SHOULD BE FIRED"));

				/*
				DrawDebugSphere
				(
					GetWorld(), EnemySelected->GetActorLocation(), 1000.0f, 10, FColor::Green, false, 10.0f, 2, 1.0f
				);
				*/
			}
			else
			{
				// do nothing, just desapear all projectiles
				GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, TEXT("NO VALID ENEMY DETECTED"));
			}
		}
	}
}

AEnemyClass* AAbility_ReversePorjectiles::SelectARandomEnemy()
{
	// chose one of the enemy
	int AmountOfEnemiesDetected = EnemiesDetected.Num();
	if (AmountOfEnemiesDetected >= 1)
	{
		int Index = FMath::RandRange(0, AmountOfEnemiesDetected - 1);

		return EnemiesDetected[Index];
	}
	else
	{
		return nullptr;
	}
	
}

void AAbility_ReversePorjectiles::ResetArrays()
{
	ActorDetected = {};
	EnemiesProjectiles = {};
	EnemiesDetected = {};
}