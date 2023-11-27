// Fill out your copyright notice in the Description page of Project Settings.


#include "Data_KillFeedBackInfo.h"


void UData_KillFeedBackInfo::InitializedAllKillFeedBacks(bool bExist, float frenzyGain,
										float calmGain, float moveSpeedGain, int XPGain)
{
	isExisted = bExist;
	frenzyReward = frenzyGain;
	calmReward = calmGain;
	moveSpeedReward = moveSpeedGain;
	XPReward = XPGain;
}

bool UData_KillFeedBackInfo::GetExistance()
{
	return isExisted;
}

float UData_KillFeedBackInfo::GetFrenzyReward()
{
	return frenzyReward;
}
float UData_KillFeedBackInfo::GetCalmReward()
{
	return calmReward;
}

float UData_KillFeedBackInfo::GetMoveSpeedReward()
{
	return moveSpeedReward;
}

int UData_KillFeedBackInfo::GetXPReward()
{
	return XPReward;
}

void UData_KillFeedBackInfo::UpdateExistance(bool modifier)
{
	isExisted = modifier;
}
void UData_KillFeedBackInfo::UpdateFrenzyReward(float modifier)
{
	frenzyReward = frenzyReward * modifier;
}
void UData_KillFeedBackInfo::UpdateCalmReward(float modifier)
{
	calmReward = calmReward * modifier;
}
void UData_KillFeedBackInfo::UpdateMoveSpeedReward(float modifier)
{
	moveSpeedReward = moveSpeedReward * modifier;
}
void UData_KillFeedBackInfo::UpdateXPReward(float modifier)
{
	XPReward = XPReward * modifier;
}