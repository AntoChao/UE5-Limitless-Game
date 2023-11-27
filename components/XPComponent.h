// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "XPComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRUEPROJECT2_API UXPComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UXPComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	float XPRatio = 2.0f;

	float xp = 0.0f;
	int level = 1;
	float xp_required = 0.0f;

	// current total work same as xp, but it never reset
	float current_total = 0.0f;
	float xp_total_gain = 0.0f;

	bool IsAbleToLevelUp();
	bool IsAbleToLevelDown();

	void LevelUp();
	void LevelDown();
	void UpdateXPRequirement();

public:
	// Setter and getter
	void SetXP(float xpAmount);
	float GetXP();

	// Level Up Logic
	void ReceiveXP(int amountXP);
	bool isAbleToBuy(int amountXP);

	// display
	float GetXPPercentage();

	FText GetLevelText();


};
