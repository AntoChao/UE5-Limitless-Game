// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Data_AbilityFeedBackInfo.generated.h"


// a container should not have any logic operation, only a container that contains infos


/* Ability Reward
	so after activate ability, it is going to give back reward to character

	For sure:
		- frenzy reward
		- calm reward
		- moment speed reward
		- reduce cooldown of ability -> should investigate:
											1- ability has the cooldown, but who start the timer
												- Character -> maybe
												- Ability System -> maybe
												- Ability -> weird weird
											2- the cooldown start when the ability is activated or when it is finished
											3- how cooldown work -> a timer which change a bool variable and dependes on the variable change the behavier
																	sound too polimorphism
											4- how to reduce the cooldown:
												- if 3 applied -> initiate other timer which simultatly work with 3 and going to finish before the 3
												- if 3 applied -> change the behaviour of 3 (no idea how to do)

		- XP of ability to return 
		- type of ability to return for ability system
		
*/

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TRUEPROJECT2_API UData_AbilityFeedBackInfo : public UDataAsset
{
	GENERATED_BODY()

private:
	// all stats container
	bool isExisted;
	float frenzyCost;
	float calmCost;
	float frenzyReward;
	float calmReward;
	float moveSpeedReward;
	int XPReward;

public:
	// Construct all variables -> not using set cuz too complicated
	// lack of cooldown, which no idea how to do it
	void InitializedAllFeedBacks(bool bExist, float frenzyUse, float calmUse, float frenzyGain,
								float calmGain, float moveSpeedGain, int XPGain);

	/*
	// Setters/ Getters of all information
	void SetFrenzyReward(float frenzyStat);
	void SetCalmReward(float CalmBoost);
	void SetMoveSpeedReward(float moveSpeedBoost);
	*/

	// In order to protect data, going to use getter and setter == initializedallfeedback
	bool GetExistance();
	float GetFrenzyCost();
	float GetCalmCost();
	float GetFrenzyReward();
	float GetCalmReward();
	float GetMoveSpeedReward();
	int GetXPReward();
};