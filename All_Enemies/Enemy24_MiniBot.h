// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyClass.h"
#include "Enemy24_MiniBot.generated.h"

UCLASS()
class LIMITLESS_API AEnemy24_MiniBot : public AEnemyClass
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemy24_MiniBot();

protected:

	// Basic Stats
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		TSubclassOf<class AWeapon_Bullet> Weapon_BulletClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Control")
		FName FirePoint_Socket = FName("Socket_Fire");

	// Basic Attack
	UFUNCTION(BlueprintCallable, Category = "BasicAttack")
		void SpawnBasicBullet();

};
