// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeneralAbilityClass.h"
#include "Ability_Open_Command.generated.h"

/*
This ability is just to spawm a black hole bomb with corresponding functionality
*/

UCLASS()
class TRUEPROJECT2_API AAbility_Open_Command : public AGeneralAbilityClass
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAbility_Open_Command(const class FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/*
	I will implement the logic on Ability system or Main
	*/

	//Open command ability will constantly checking main input -> but these input may 
	// be stored in ability system -> which is better idea "maybe"
	// enum/ bool of main
	bool IsStillRunning;
	// access main to check the key value
		// if it is esc -> exit
		// if it is enter -> start a new letter and check if the existed letter mean anything
		// otherwise -> record it
	void CheckInput();
	// when press enter -> need to validate the input
	// input result
		// command 1 -> infinitive frenzy/ calm
		// command 2 -> gamemode 1
		// command 3 -> ...
	void ValidateInput();
	void ExecuteTheCommand();

public:	
	virtual bool AbilityRequirement(UData_AbilityRequiredInfo* requiredInfo) override;

	virtual void ActivateAbilityEffect(UData_AbilityRequiredInfo* requiredInfo) override;
};
