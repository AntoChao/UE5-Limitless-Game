// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyClass.h"
#include "../meshes/Weapon_Bullet.h"
#include "Enemy26_Spider_Queen.generated.h"

UCLASS()
class LIMITLESS_API AEnemy26_Spider_Queen : public AEnemyClass
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemy26_Spider_Queen();

protected:
	// Basic Stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats Need To Set")
		UAnimMontage* AnimMontage_JumpStandAttack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats Need To Set")
		UAnimMontage* AnimMontage_JumpLaunchAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats Need To Set")
		float StunTime = 5.0f;
	UFUNCTION(BlueprintCallable, Category = "BasicAttack")
		void BasicAttackStun();
	UFUNCTION(BlueprintCallable, Category = "BasicAttack")
		void BasicAttackDealDamage();

	UFUNCTION(BlueprintCallable, Category = "BasicAttack")
		void SpawnSpiderBullet();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "BasicAttack")
		void SpawnGroundHitNiagara();

		/*Ability 1*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		TSubclassOf<class AWeapon_Bullet> Weapon_BulletClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Control")
		FName Weapon_FirePoint_Socket = FName("Socket_Fire");

};
