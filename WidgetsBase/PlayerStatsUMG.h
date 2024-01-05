// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../Common_Enums.h"

#include "PlayerStatsUMG.generated.h"

UCLASS()
class LIMITLESS_API UPlayerStatsUMG : public UUserWidget
{
	GENERATED_BODY()

protected:
	// Variables to display
	// Objectives
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Stats")
		FText CurrentObjective;

	// Health frenzy calm 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Stats")
		float HealthPercentageToDisplay = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Stats")
		float FrenzyPercentageToDisplay = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Stats")
		float CalmPercentageToDisplay = 0.0f;

	// XP
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Stats")
		FText LVToDisplay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Stats")
		float XPPercentageToDisplay = 0.0f;

	// Time 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Time")
		int CurrentSeg;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Time")
		int CurrentHour;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Time")
		int CurrentDay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Time")
		bool IsInMorning = false;

public:
	UFUNCTION(BlueprintCallable, Category = "Display Stats")
		void SetHealth(float HealthPercentage);
	UFUNCTION(BlueprintCallable, Category = "Display Stats")
		void SetFrenzy(float FrenzyPercentage);
	UFUNCTION(BlueprintCallable, Category = "Display Stats")
		void SetCalm(float CalmPercentage);

	UFUNCTION(BlueprintCallable, Category = "Display Stats")
		void SetLevelNumber(FText LevelTxt);
	UFUNCTION(BlueprintCallable, Category = "Display Stats")
		void SetLevelPercentage(float LevelPercentage);

	UFUNCTION(BlueprintCallable, Category = "Display Time")
		void SetSeconds(float Seconds);
	UFUNCTION(BlueprintCallable, Category = "Display Time")
		void SetHours(float Hours);
	UFUNCTION(BlueprintCallable, Category = "Display Time")
		void SetDay(float Days);

	UFUNCTION(BlueprintCallable, Category = "Display Time")
		void SetIsInMorning(bool bInMorining);

	UFUNCTION(BlueprintCallable, Category = "Display Time")
		void UpdateObjective(FText NewObjective);

};
