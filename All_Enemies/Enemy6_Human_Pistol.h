// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyClass.h"
#include "../meshes/Weapon_Pistol.h"
#include "../meshes/Weapon_Bullet.h"
#include "Enemy6_Human_Pistol.generated.h"

UCLASS()
class LIMITLESS_API AEnemy6_Human_Pistol : public AEnemyClass
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemy6_Human_Pistol();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Basic Stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		TSubclassOf<class AWeapon_Pistol> Weapon_PistolClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		class AWeapon_Pistol* Weapon_Pistol;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		TSubclassOf<class AWeapon_Bullet> Weapon_BulletClass;

	UFUNCTION(BlueprintCallable)
		void SpawnPistolInHand();

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
		float FireOffset = 50.0f;

	UFUNCTION(BlueprintCallable, Category = "Fire")
		FVector CalculateFireDestination();
	
	UFUNCTION(BlueprintCallable, Category = "Fire")
		void Fire(FVector Destination);

	// Ability 1 -> StandingStill shot very fast for X seconds
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability 1")
		int ShotTime = 15.0f;


public:	
	// Called every frame
	virtual void CustomTickFunction() override;

	virtual void BasicAttack() override;
	virtual void Ability1() override;

};
