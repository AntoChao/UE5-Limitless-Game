// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "data_killfeedbackinfo.generated.h"

UCLASS()
class TRUEPROJECT2_API UData_KillFeedBackInfo : public UDataAsset
{
	GENERATED_BODY()

private:
	// all stats container
	bool isExisted;
	float frenzyReward;
	float calmReward;
	float moveSpeedReward;
	int XPReward;

public:
	// Construct all variables -> not using set cuz too complicated
	// lack of cooldown, which no idea how to do it
	void InitializedAllKillFeedBacks(bool bExist, float frenzyGain, float calmGain,
		float moveSpeedGain, int XPGain);

	// In order to protect data, going to use getter and setter == initializedallfeedback
	bool GetExistance();
	float GetFrenzyReward();
	float GetCalmReward();
	float GetMoveSpeedReward();
	int GetXPReward();

	void UpdateExistance(bool modifier);
	void UpdateFrenzyReward(float modifier);
	void UpdateCalmReward(float modifier);
	void UpdateMoveSpeedReward(float modifier);
	void UpdateXPReward(float modifier);


};