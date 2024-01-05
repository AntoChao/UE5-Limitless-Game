// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeneralAbilityClass.h"
#include "Ability_AlienGun.generated.h"

UCLASS()
class LIMITLESS_API AAbility_AlienGun : public AGeneralAbilityClass
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAbility_AlienGun(const class FObjectInitializer& ObjectInitialize);

protected:
	
	// specific stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		class AEnemyClass* Enemy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MuzzleOffSet")
		FVector MuzzleOffset;

public:
	virtual void ActivateAbilityEffect(UData_AbilityRequiredInfo* requiredInfo) override;

};
