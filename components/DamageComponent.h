// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterPowerComponent.h"
#include "DamageComponent.generated.h"

/* Damage Component
* Every actor that is able to deal damage should have a damage component
* Which contain information such as: base dmg, crit prob...
* Is able to receive character stats -> update new values...
* Character should not have this component, as they do not deal damage directly
*/ 
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LIMITLESS_API UDamageComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDamageComponent();

protected:
	// Basic Stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Control")
		float baseDamage = 0.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Control")
		float critChance = 0.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Control")
		float critMultiplier = 0.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Control")
		float fireRate = 1.0f;

public:	
	// Getters and Setters
	UFUNCTION(BlueprintCallable, Category = "Damage Control")
		void SetDamage(float damageValue);

	UFUNCTION(BlueprintCallable, Category = "Damage Control")
		float GetDamage();
	
	UFUNCTION(BlueprintCallable, Category = "Damage Control")
		void SetCritChance(float critChanceValue);
	
	UFUNCTION(BlueprintCallable, Category = "Damage Control")
		float GetCritChance();
	
	UFUNCTION(BlueprintCallable, Category = "Damage Control")
		void SetCritMultiplier(float critMultiplierValue);
	
	UFUNCTION(BlueprintCallable, Category = "Damage Control")
		float GetCritMultiplier();
	
	UFUNCTION(BlueprintCallable, Category = "Damage Control")
		void SetFireRate(float fireRateValue);
	
	UFUNCTION(BlueprintCallable, Category = "Damage Control")
		float GetFireRate();

	// Futher functionalities
};
