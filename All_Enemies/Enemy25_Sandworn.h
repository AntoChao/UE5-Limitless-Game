// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyClass.h"
#include "../meshes/Weapon_Bullet.h"
#include "Enemy25_Sandworn.generated.h"

UCLASS()
class LIMITLESS_API AEnemy25_Sandworn : public AEnemyClass
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemy25_Sandworn();

protected:

	// Basic Stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		TSubclassOf<class AWeapon_Bullet> Weapon_BulletClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Control")
		FName FirePoint_Socket = FName("Socket_Fire");
	UFUNCTION(BlueprintCallable, Category = "Explotion")
		void SpawnSandBullet();

};
