// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FrenzyComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRUEPROJECT2_API UFrenzyComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFrenzyComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	float frenzy = 0.0f;
	float maxFrenzy = 100.0f;

public:	
	
	// setters and getters, can be stats/ cost/ reward
	void SetFrenzy(float frenzyAmount);
	float GetFrenzy();
	void SetMaxFrenzy(float maxFrenzyAmount);
	float GetMaxFrenzy();

	// to UI the percentage
	float GetFrenzyPercentage();

	// update character frenzy value
	void UpdateFrenzy(float modifier);
	void UpdateMaxFrenzy(float modifier);

	/*calculate specific frenzy value for abilities
	SHOULD BE PART OF ABILITIES -> FRENZY SHOULD NOT ADAPT ABILITY COST
	virtual float CalculateFrenzyCost();
	virtual float CalculateFrenzyReward();
	*/
};
