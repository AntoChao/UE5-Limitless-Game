// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeneralAbilityClass.h"
#include "Ability_Teleport.generated.h"

/*
This ability is just to spawm a black hole bomb with corresponding functionality
*/

UCLASS()
class TRUEPROJECT2_API AAbility_Teleport : public AGeneralAbilityClass
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAbility_Teleport(const class FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Stats")
		TSubclassOf<class AWeapon_TeleportMark> AWeapon_TeleportMarkClass;

	// Basic stats
	// Ability Requirement
	void IsAbleToTP(UData_AbilityRequiredInfo* requiredInfo);
	void IsAbleToCreateMark(UData_AbilityRequiredInfo* requiredInfo);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Stats")
		bool bAbleToTP = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Stats")
		bool bAbleToCreateMark = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Stats")
		float ViewRange = 500.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Stats")
		int MarkCharges = 3; // amount of mark allow
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Stats")
		TArray<AWeapon_TeleportMark*> TeleportMarkList = {}; // marks placed in world
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Stats")
		TArray<float> MarkDistances = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Stats")
		float MinDistance = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Stats")
		int SelectedIndex = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Stats")
		class AWeapon_TeleportMark* MarkSelected = nullptr; // for tp, get it by index

	// Ability Teleport effect
	void TP(UData_AbilityRequiredInfo* requiredInfo);
	void CreateNewTPMark(UData_AbilityRequiredInfo* requiredInfo);
	void EliminateTPMark(AWeapon_TeleportMark* AMark);

public:	
	virtual bool AbilityRequirement(UData_AbilityRequiredInfo* requiredInfo) override;
	virtual void ActivateAbilityEffect(UData_AbilityRequiredInfo* requiredInfo) override;

	bool GetIsAbleToTP();
	bool GetIsAbleToPutMark();

};
