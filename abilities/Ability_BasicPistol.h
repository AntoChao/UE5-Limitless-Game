// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeneralAbilityClass.h"
#include "Ability_BasicPistol.generated.h"

UCLASS(Blueprintable, BlueprintType)
class LIMITLESS_API AAbility_BasicPistol : public AGeneralAbilityClass
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAbility_BasicPistol(const class FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		class AEnemyClass* Enemy;

	// specific stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
		float MaxDistance = 3000.0f;

public:	
	virtual void ActivateAbilityEffect(UData_AbilityRequiredInfo* requiredInfo) override;

	// virtual void ApplyDamageToEnemy(UData_AbilityRequiredInfo* requiredInfo) override;
	virtual float CalculateSpecialDamage(UData_AbilityRequiredInfo* requiredInfo) override;
};
