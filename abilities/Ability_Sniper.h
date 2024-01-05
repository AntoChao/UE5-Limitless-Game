// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeneralAbilityClass.h"
#include "Ability_Sniper.generated.h"

UCLASS()
class LIMITLESS_API AAbility_Sniper : public AGeneralAbilityClass
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAbility_Sniper(const class FObjectInitializer& ObjectInitializer);

protected:
	// specific stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Stats")
		float MaxDistance = 3000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		class AEnemyClass* Enemy;

public:	
	virtual void ActivateAbilityEffect(UData_AbilityRequiredInfo* requiredInfo) override;

	virtual float CalculateSpecialDamage(UData_AbilityRequiredInfo* requiredInfo) override;
};
