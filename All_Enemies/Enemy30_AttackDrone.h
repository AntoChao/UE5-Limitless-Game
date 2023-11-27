// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyClass.h"
#include "Enemy30_AttackDrone.generated.h"

UCLASS()
class TRUEPROJECT2_API AEnemy30_AttackDrone : public AEnemyClass
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemy30_AttackDrone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//Basic Stats
	FHitResult EnemyHit;
	
	FComponentQueryParams DefaultComponentQueryParams;
	FCollisionResponseParams DefaultResponseParam;

	// Ability 1 -> Fire 8 missiles
	FName Mossile_N1 = FName("Socket_Missle1");
	FName Mossile_N2 = FName("Socket_Missle2");
	FName Mossile_N3 = FName("Socket_Missle3");
	FName Mossile_N4 = FName("Socket_Missle4");
	FName Mossile_N5 = FName("Socket_Missle5");
	FName Mossile_N6 = FName("Socket_Missle6");
	FName Mossile_N7 = FName("Socket_Missle7");
	FName Mossile_N8 = FName("Socket_Missle8");

	UPROPERTY(EditAnywhere, Category = "Ability")
		TSubclassOf<class AWeapon_Missile> Weapon_MissileClass;
	
	UFUNCTION(BlueprintCallable)
		void SpawnMissiles();

	virtual FVector GetAttackFinishedPosition() override;

};
