// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyClass.h"
#include "Enemy27_Swat.generated.h"

UCLASS()
class TRUEPROJECT2_API AEnemy27_Swat : public AEnemyClass
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemy27_Swat();

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
		void SpawnRifleInHand();

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

	// BasicAttack -> normal fire
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BasicAttack")
		float FireOffset = 300.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability 1")
		int ShotTime = 15.0f;

	UFUNCTION(BlueprintCallable, Category = "Fire")
		FVector CalculateFireDestination();

	UFUNCTION(BlueprintCallable, Category = "Fire")
		void Fire(FVector Destination);
	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Fire")
		void SpawnFireNiagara();

public:

	virtual void BasicAttack() override;
	virtual void Ability1() override;
};
