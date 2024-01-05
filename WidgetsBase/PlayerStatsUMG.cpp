// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStatsUMG.h"
#include "Components/ProgressBar.h"
#include "Math/UnrealMathUtility.h"

// Character Level
void UPlayerStatsUMG::SetHealth(float HealthPercentage) {
	HealthPercentageToDisplay = HealthPercentage;
}

void UPlayerStatsUMG::SetFrenzy(float FrenzyPercentage) {
	FrenzyPercentageToDisplay = FrenzyPercentage;
}

void UPlayerStatsUMG::SetCalm(float CalmPercentage) {
	CalmPercentageToDisplay = CalmPercentage;
}

void UPlayerStatsUMG::SetLevelNumber(FText LevelTxt) {
	LVToDisplay = LevelTxt;
}

void UPlayerStatsUMG::SetLevelPercentage(float LevelPercentage) {
	XPPercentageToDisplay = LevelPercentage;
}

// Time
void UPlayerStatsUMG::SetSeconds(float Seconds) {
	/*
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, TEXT("Seconds:"));
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, FString::SanitizeFloat(Seconds));
	*/
	CurrentSeg = FMath::RoundToInt(Seconds);
}
void UPlayerStatsUMG::SetHours(float Hours) {
	CurrentHour = FMath::RoundToInt(Hours);
}
void UPlayerStatsUMG::SetDay(float Days) {
	CurrentDay = FMath::RoundToInt(Days);
}

void UPlayerStatsUMG::SetIsInMorning(bool bInMorining) {
	IsInMorning = bInMorining;
}

// Objectives
void UPlayerStatsUMG::UpdateObjective(FText NewObjective) {
	CurrentObjective = NewObjective;
}