// Fill out your copyright notice in the Description page of Project Settings.


#include "Data_AbilityFeedBackInfo.h"

// Sets default values
/*
UData_AbilityFeedBackInfo::UData_AbilityFeedBackInfo()
{

}
*/

void UData_AbilityFeedBackInfo::InitializedAllFeedBacks(bool bExist, float frenzyUse,
	float calmUse, float frenzyGain, float calmGain, float moveSpeedGain, int XPGain)
{
	isExisted = bExist;
	frenzyCost = frenzyUse;
	calmCost = calmUse;
	frenzyReward = frenzyGain;
	calmReward = calmGain;
	moveSpeedReward = moveSpeedGain;
	XPReward = XPGain;
}

bool UData_AbilityFeedBackInfo::GetExistance()
{
	return isExisted;
}

float UData_AbilityFeedBackInfo::GetFrenzyCost()
{
	return frenzyCost;
}

float UData_AbilityFeedBackInfo::GetCalmCost()
{
	return calmCost;
}

float UData_AbilityFeedBackInfo::GetFrenzyReward()
{
	return frenzyReward;
}

float UData_AbilityFeedBackInfo::GetCalmReward()
{
	return calmReward;
}

float UData_AbilityFeedBackInfo::GetMoveSpeedReward()
{
	return moveSpeedReward;
}

int UData_AbilityFeedBackInfo::GetXPReward()
{
	return XPReward;
}
