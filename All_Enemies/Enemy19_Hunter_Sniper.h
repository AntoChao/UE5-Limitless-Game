// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyClass.h"
#include "../meshes/Weapon_SniperRifle.h"
#include "../meshes/Weapon_Bullet.h"
#include "Enemy19_Hunter_Sniper.generated.h"

UCLASS()
class LIMITLESS_API AEnemy19_Hunter_Sniper : public AEnemyClass
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemy19_Hunter_Sniper();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Basic Stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		TSubclassOf<class AWeapon_SniperRifle> Weapon_SniperRifleClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		class AWeapon_SniperRifle* Weapon_SniperRifle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		TSubclassOf<class AWeapon_Bullet> Weapon_BulletClass;

	UFUNCTION(BlueprintCallable)
		void SpawnSniperInHand();

	UFUNCTION(BlueprintCallable)
		void UpdateSocketsInfo();

	/*the pistol is attached in the left hand
	* and set the right hand in the position of pistol socket	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Control")
		FName Enemy_LeftHand_Socket = FName("Socket_LeftHand");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Control")
		FName Weapon_RightHand_Socket = FName("Socket_Right_Hand");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Control")
		FName Weapon_FirePoint_Socket = FName("Socket_Fire");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Control")
		FVector LeftHandPosition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Control")
		FVector WeaponFirePosition;

	// BasicAttack -> Shoting while moving? -> use ability but instant finish it
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BasicAttack")
		float FireOffset = 300.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability 1")
		int ShotTime = 15.0f;

	UFUNCTION(BlueprintCallable, Category = "Fire")
		FVector CalculateFireDestination();

	UFUNCTION(BlueprintCallable, Category = "Fire")
		void Fire(FVector Destination);

	// Ability 1 -> Throw smoke
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "AbilityOne")
		void SpawnSmokeNiagara();

public:
	// Called every frame
	virtual void CustomTickFunction() override;

	virtual void BasicAttack() override;
	virtual void Ability1() override;
};
