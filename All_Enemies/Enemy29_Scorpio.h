// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyClass.h"
#include "Enemy29_Scorpio.generated.h"

UCLASS()
class TRUEPROJECT2_API AEnemy29_Scorpio : public AEnemyClass
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemy29_Scorpio();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Basic Stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		TSubclassOf<class AWeapon_Bullet> Weapon_BulletClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Control")
		FName FirePoint_Socket = FName("Socket_Fire");
	UFUNCTION(BlueprintCallable, Category = "Explotion")
		void SpawnSandBullet();


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void BasicAttack() override;
	virtual void Ability1() override;
};
