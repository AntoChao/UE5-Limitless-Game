// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeneralAbilityClass.h"
#include "Ability_ReversePorjectiles.generated.h"

/*
This ability is just detect all enemies weapons in X radius, 
replace them to reverse Projectile and add impulse to them in reverse Direction.
*/

UCLASS()
class LIMITLESS_API AAbility_ReversePorjectiles : public AGeneralAbilityClass
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAbility_ReversePorjectiles(const class FObjectInitializer& ObjectInitializer);

protected:
	UFUNCTION(BlueprintCallable, Category = "Effect")
		void ResetArrays();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
		TArray<class AActor*> ActorsDetected;
	UFUNCTION(BlueprintCallable, Category = "Effect")
		void GetAllEnemiesProjectiles(UData_AbilityRequiredInfo* requiredInfo);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
		float RadiusOfDetection = 5000.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
		TArray<class AWeapon_GProjectileClass*> EnemiesProjectiles = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
		TArray<class AEnemyClass*> EnemiesDetected = {};
	UFUNCTION(BlueprintCallable, Category = "Effect")
		void SetAllProjectiles(UData_AbilityRequiredInfo* requiredInfo);
	UFUNCTION(BlueprintCallable, Category = "Effect")
		AEnemyClass* SelectARandomEnemy();

	UPROPERTY(EditAnywhere, Category = "Projectile")
		TSubclassOf<class AWeapon_ReverseProjectile> Weapon_ReverseProjectileClass;

public:	
	virtual void ActivateAbilityEffect(UData_AbilityRequiredInfo* requiredInfo) override;
};
