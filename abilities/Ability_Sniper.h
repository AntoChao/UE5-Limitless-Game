// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeneralAbilityClass.h"
#include "Ability_Sniper.generated.h"

UCLASS()
class TRUEPROJECT2_API AAbility_Sniper : public AGeneralAbilityClass
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAbility_Sniper(const class FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// specific stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Stats")
		FVector DistanceVector;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Stats")
		float Distance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		class AEnemyClass* Enemy;

public:	
	virtual bool AbilityRequirement(UData_AbilityRequiredInfo* requiredInfo) override;

	virtual void ActivateAbilityEffect(UData_AbilityRequiredInfo* requiredInfo) override;

	virtual float CalculateSpecialDamage(UData_AbilityRequiredInfo* requiredInfo) override;
};
