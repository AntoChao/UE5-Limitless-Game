// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterPowerComponent.generated.h"

/* Damage Component
* Every actor that is able to deal damage should have a damage component
* Which contain information such as: base dmg, crit prob...
* Is able to receive character stats -> update new values...
* Character should not have this component, as they do not deal damage directly
*/ 
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LIMITLESS_API UCharacterPowerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCharacterPowerComponent();

protected:
	// Basic Stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power Control")
		float characBasePower = 5.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power Control")
		float characBaseCritChance = 5.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power Control")
		float characBaseCritMultipier = 1.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power Control")
		float characAttackRate = 1.0f;

public:	
	// Setters and Getters
	UFUNCTION(BlueprintCallable, Category = "Power Control")
		void SetPower(float PowerValue);
	
	UFUNCTION(BlueprintCallable, Category = "Power Control")
		float GetPower();
	
	UFUNCTION(BlueprintCallable, Category = "Power Control")
		void SetCharacCritChance(float critChanceValue);
	
	UFUNCTION(BlueprintCallable, Category = "Power Control")
		float GetCharacCritChance();
	
	UFUNCTION(BlueprintCallable, Category = "Power Control")
		void SetCharacCritMultiplier(float critMultiplierValue);
	
	UFUNCTION(BlueprintCallable, Category = "Power Control")
		float GetCharacCritMultiplier();
	
	UFUNCTION(BlueprintCallable, Category = "Power Control")
		void SetCharacAttackRate(float attackRateValue);

	UFUNCTION(BlueprintCallable, Category = "Power Control")
		float GetCharacAttackRate();

	// Updates Values
	UFUNCTION(BlueprintCallable, Category = "Power Control")
		void UpdateFlatPower(float modifier);
	
	UFUNCTION(BlueprintCallable, Category = "Power Control")
		void UpdatePercentagePower(float modifier);
	
	UFUNCTION(BlueprintCallable, Category = "Power Control")
		void UpdateCritChance(float modifier);
	
	UFUNCTION(BlueprintCallable, Category = "Power Control")
		void UpdateCritMultiplier(float modifier);
	
	UFUNCTION(BlueprintCallable, Category = "Power Control")
		void UpdateAttackRate(float modifier);
};
