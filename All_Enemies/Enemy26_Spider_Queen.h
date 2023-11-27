// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyClass.h"
#include "../meshes/Weapon_Bullet.h"
#include "Enemy26_Spider_Queen.generated.h"

UCLASS()
class TRUEPROJECT2_API AEnemy26_Spider_Queen : public AEnemyClass
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemy26_Spider_Queen();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Basic Stats
		/*Basic Attack*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats Need To Set")
		float AttackDistance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats Need To Set")
		bool IsInDistance = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats Need To Set")
		UAnimMontage* AnimMontage_JumpStandAttack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats Need To Set")
		UAnimMontage* AnimMontage_JumpLaunchAttack;

	UFUNCTION(BlueprintCallable, Category = "BasicAttack")
		void SpawnSpiderBullet();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "BasicAttack")
		void SpawnGroundHitNiagara();

		/*Ability 1*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		TSubclassOf<class AWeapon_Bullet> Weapon_BulletClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Control")
		FName Weapon_FirePoint_Socket = FName("Socket_Fire");


public:
	// basic attack -> walk close to player and attack the ground
	virtual void BasicAttack() override;
	virtual void BasicAttackFinished() override;
	virtual void PlayAnimBasicAttack() override;

	// ability one -> fire a web bullet
	virtual void Ability1() override;
};
