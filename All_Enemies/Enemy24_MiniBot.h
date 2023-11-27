// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyClass.h"
#include "Enemy24_MiniBot.generated.h"

UCLASS()
class TRUEPROJECT2_API AEnemy24_MiniBot : public AEnemyClass
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemy24_MiniBot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Basic Stats
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		TSubclassOf<class AWeapon_Bullet> Weapon_BulletClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Control")
		FName FirePoint_Socket = FName("Socket_Fire");

	// Basic Attack
	UFUNCTION(BlueprintCallable, Category = "BasicAttack")
		void SpawnBasicBullet();

	// Ability 1 -> ???

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// Always moving, the basic attack logic should be in c++ code
	virtual void CustomTickFunction() override;

	virtual void BasicAttack() override;

	

	virtual void Ability1() override;
};
