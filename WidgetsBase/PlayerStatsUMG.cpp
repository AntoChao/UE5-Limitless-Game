// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStatsUMG.h"
#include "Components/ProgressBar.h"


// Character Level
void UPlayerStatsUMG::SetHealth(float HealthPercentage)
{
	HealthPercentageToDisplay = HealthPercentage;
}

void UPlayerStatsUMG::SetFrenzy(float FrenzyPercentage)
{
	FrenzyPercentageToDisplay = FrenzyPercentage;
}

void UPlayerStatsUMG::SetCalm(float CalmPercentage)
{
	CalmPercentageToDisplay = CalmPercentage;
}

void UPlayerStatsUMG::SetLevelNumber(FText LevelTxt)
{
	LVToDisplay = LevelTxt;
}

void UPlayerStatsUMG::SetLevelPercentage(float LevelPercentage)
{
	XPPercentageToDisplay = LevelPercentage;
}

// Time
void UPlayerStatsUMG::SetTimeString(FText ATime)
{
	TimeStringToDisplay = ATime;
}

void UPlayerStatsUMG::SetTime(float TimePercentage)
{
	TimePercentageToDisplay = TimePercentage;
}
void UPlayerStatsUMG::SetIsInMorning(bool bInMorining)
{
	IsInMorning = bInMorining;
}

// Objectives
void UPlayerStatsUMG::HandleObjectives()
{
	return;
}