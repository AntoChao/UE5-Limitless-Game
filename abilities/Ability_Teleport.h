// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeneralAbilityClass.h"
#include "Ability_Teleport.generated.h"

/*
This ability is just to spawm a black hole bomb with corresponding functionality
*/

UCLASS()
class LIMITLESS_API AAbility_Teleport : public AGeneralAbilityClass
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAbility_Teleport(const class FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Stats")
		TSubclassOf<class AWeapon_TeleportMark> AWeapon_TeleportMarkClass;

	// Basic stats
	// Ability Requirement

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Stats")
		float ViewRange = 500.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Stats")
		TArray<AWeapon_TeleportMark*> TeleportMarkList = {}; // marks placed in world

public:	
	virtual void ActivateAbilityEffect(UData_AbilityRequiredInfo* requiredInfo) override;
};
