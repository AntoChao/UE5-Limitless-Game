// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyClass.h"
#include "Enemy10_Robot_Papu.generated.h"

UCLASS()
class TRUEPROJECT2_API AEnemy10_Robot_Papu : public AEnemyClass
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemy10_Robot_Papu();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Basic Stats
	UPROPERTY(EditAnywhere, Category = "Enemies")
		TSubclassOf<class AMain> MainClass;

	FHitResult EnemyHit;
	
	FComponentQueryParams DefaultComponentQueryParams;
	FCollisionResponseParams DefaultResponseParam;

	float WalkSpeed;

	// FRotator InitRotation;

	// Ability 1 -> Spawn Drones
	FName Drone1_Socket = FName("Drone1_Socket");
	FName Drone2_Socket = FName("Drone2_Socket");
	FName Drone3_Socket = FName("Drone3_Socket");
	FName Drone4_Socket = FName("Drone4_Socket");

	UPROPERTY(EditAnywhere, Category = "Ability")
		TSubclassOf<class AEnemy30_AttackDrone> AttackDroneClass;

	// void CalculateDroneSpawnStats();
	
	UFUNCTION(BlueprintCallable)
		void SpawnAttackDrones();

	// Ability 2 -> OP Laser
	FName Head_Laser_Socket = FName("Head_Laser_Socket");

	UPROPERTY(EditAnywhere, Category = "Ability")
		TSubclassOf<class AWeapon_Laser> LaserClass;
	UPROPERTY(EditAnywhere, Category = "Ability")
		class AWeapon_Laser* Weapon_Laser;

	UFUNCTION(BlueprintCallable)
		void SpawnLaser();

	// Ability 3 -> Gen attack
	FName Hand_Diamond_Socket = FName("RightHand_Diamond_Socket");

	UPROPERTY(EditAnywhere, Category = "Ability")
		TSubclassOf<class AWeapon_Gem> GemClass;
	UPROPERTY(EditAnywhere, Category = "Ability")
		class AWeapon_Gem* Weapon_Gem1;
	UPROPERTY(EditAnywhere, Category = "Ability")
		class AWeapon_Gem* Weapon_Gem2;
	UPROPERTY(EditAnywhere, Category = "Ability")
		class AWeapon_Gem* Weapon_Gem3;

	UFUNCTION(BlueprintCallable)
		void SpawnGem();


public:	
	// Called every frame
	// virtual void Tick(float DeltaTime) override;
};
