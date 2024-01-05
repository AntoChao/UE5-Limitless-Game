// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeneralAbilityClass.h"
#include "Ability_WireTrap.generated.h"

/*
This ability is just to spawm a black hole bomb with corresponding functionality
*/

UCLASS()
class LIMITLESS_API AAbility_WireTrap : public AGeneralAbilityClass
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAbility_WireTrap(const class FObjectInitializer& ObjectInitializer);

protected:
	UFUNCTION(BlueprintCallable, Category = "Bomb")
		void SpawnBlackHoleBomb(UData_AbilityRequiredInfo* requiredInfo);

	// no idea if i need it or not
	//virtual void WaitingPlayerDecision(UData_AbilityRequiredInfo* requiredInfo) override;

public:	
	virtual void ActivateAbilityEffect(UData_AbilityRequiredInfo* requiredInfo) override;

};
