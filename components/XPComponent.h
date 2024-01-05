// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "XPComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LIMITLESS_API UXPComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UXPComponent();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XP Component")
		float XPRatio = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XP Component")
		float xp = 0.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XP Component")
		int level = 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XP Component")
		float xp_required = 10.0f;

	// current total work same as xp, but it never reset
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XP Component")
		float current_total = 0.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XP Component")
		float xp_total_gain = 0.0f;

	UFUNCTION(BlueprintCallable, Category = "XP Component")
		bool IsAbleToLevelUp();
	
	UFUNCTION(BlueprintCallable, Category = "XP Component")
		bool IsAbleToLevelDown();

	UFUNCTION(BlueprintCallable, Category = "XP Component")
		void LevelUp();
	UFUNCTION(BlueprintCallable, Category = "XP Component")
		void LevelDown();
	UFUNCTION(BlueprintCallable, Category = "XP Component")
		void UpdateXPRequirement();

public:
	// Setter and getter
	UFUNCTION(BlueprintCallable, Category = "XP Component")
		void SetXP(float xpAmount);
	UFUNCTION(BlueprintCallable, Category = "XP Component")
		float GetXP();
	UFUNCTION(BlueprintCallable, Category = "XP Component")
		float GetTotalXPRequired();

	// Level Up Logic
	UFUNCTION(BlueprintCallable, Category = "XP Component")
		void ReceiveXP(int amountXP);
	UFUNCTION(BlueprintCallable, Category = "XP Component")
		bool isAbleToBuy(int amountXP);

	// display
	UFUNCTION(BlueprintCallable, Category = "XP Component")
		float GetXPPercentage();

	UFUNCTION(BlueprintCallable, Category = "XP Component")
		FText GetLevelText();
};
