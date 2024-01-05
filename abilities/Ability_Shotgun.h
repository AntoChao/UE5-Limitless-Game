// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeneralAbilityClass.h"
#include "Ability_Shotgun.generated.h"

UCLASS()
class LIMITLESS_API AAbility_Shotgun : public AGeneralAbilityClass
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAbility_Shotgun(const class FObjectInitializer& ObjectInitializer);

protected:
	// Weapon Stats Simulating Shotgun
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
		int NumberOfTraces = 30;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
		float ConeAngle = 45.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
		float MaxDistance = 1000.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
		float SingleBulletDamage = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		class AEnemyClass* Enemy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MuzzleOffSet")
		FVector MuzzleOffset;

public:
	virtual void ActivateAbilityEffect(UData_AbilityRequiredInfo* requiredInfo) override;
	
	TArray<FVector> CalculateSpreadDirections(FVector ShotgunLocation, 
		FVector DestinationLocation);

	float CalculateShotgunDamage(FHitResult HitResult,
		UData_AbilityRequiredInfo* requiredInfo);
};
