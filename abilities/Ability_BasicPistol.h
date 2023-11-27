// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeneralAbilityClass.h"
#include "Ability_BasicPistol.generated.h"

UCLASS(Blueprintable, BlueprintType)
class TRUEPROJECT2_API AAbility_BasicPistol : public AGeneralAbilityClass
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
		FVector DistanceVector;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
		float Distance;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	virtual bool AbilityRequirement(UData_AbilityRequiredInfo* requiredInfo) override;
	
	virtual void ActivateAbilityEffect(UData_AbilityRequiredInfo* requiredInfo) override;

	// virtual void ApplyDamageToEnemy(UData_AbilityRequiredInfo* requiredInfo) override;
	virtual float CalculateSpecialDamage(UData_AbilityRequiredInfo* requiredInfo) override;
};
