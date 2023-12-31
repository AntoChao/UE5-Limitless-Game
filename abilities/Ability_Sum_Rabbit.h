// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeneralAbilityClass.h"
#include "Ability_Sum_Rabbit.generated.h"

/*
This ability is just to spawm a black hole bomb with corresponding functionality
*/

UCLASS()
class LIMITLESS_API AAbility_Sum_Rabbit : public AGeneralAbilityClass
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAbility_Sum_Rabbit(const class FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Stats")
		TSubclassOf<class AEnemy31_KillerRabbit> Enemy31_KillerRabbitClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Stats")
		AEnemy31_KillerRabbit* KillerRabbit;

	UFUNCTION(BlueprintCallable, Category = "Foot")
		void SpawnRabbit(UData_AbilityRequiredInfo* requiredInfo);

public:	

	virtual void ActivateAbilityEffect(UData_AbilityRequiredInfo* requiredInfo) override;

};
