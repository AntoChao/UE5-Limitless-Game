// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyClass.h"
#include "../meshes/Weapon_Bullet.h"
#include "Enemy9_Robot_Girl.generated.h"

UCLASS()
class LIMITLESS_API AEnemy9_Robot_Girl : public AEnemyClass
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemy9_Robot_Girl();

protected:

	// Basic Stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		TSubclassOf<class AWeapon_Bullet> Weapon_BulletClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		class AWeapon_Bullet* Bullet;

	// Basic Attack
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BasicAttack")
		int AmountOfOrbs = 5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BasicAttack")
		float OrbSpawnDistance = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BasicAttack")
		float OrbDestinationDistance = 3000.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BasicAttack")
		float AroundHeight = 100.0f;
	/* Basic Attack -> Spawn "bullet" all around the girl robot and send it*/
	UFUNCTION(BlueprintCallable)
		void SpawnBasicAttackOrbs();


	// Ability 1
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilityOne")
		int AmountOfPortalOrbs = 50;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilityOne")
		float PortalHeight = 500.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilityOne")
		float DestinationOffSet = 1000.0f;
	UFUNCTION(BlueprintCallable)
		FVector CalculatePortalOrbDestination();
	/* Robot girl stand still, Create a portal above her and spawn infinite bullet around the player*/
	UFUNCTION(BlueprintCallable)
		void SpawnAbilityOneOrbs();

public:
};
