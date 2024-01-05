// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeneralAbilityClass.h"
#include "Ability_BlackHoleBomb.generated.h"

/*
This ability is just to spawm a black hole bomb with corresponding functionality
*/

UCLASS()
class LIMITLESS_API AAbility_BlackHoleBomb : public AGeneralAbilityClass
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAbility_BlackHoleBomb(const class FObjectInitializer& ObjectInitializer);

protected:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Bomb")
		void SpawnBlackHoleBomb(UData_AbilityRequiredInfo* requiredInfo);

public:	
	virtual void ActivateAbilityEffect(UData_AbilityRequiredInfo* requiredInfo) override;

};
