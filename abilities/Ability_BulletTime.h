// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeneralAbilityClass.h"
#include "Ability_BulletTime.generated.h"

UCLASS()
class LIMITLESS_API AAbility_BulletTime : public AGeneralAbilityClass
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAbility_BulletTime(const class FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Over")
		float MinTimeDilation = 0.05f;
	UFUNCTION(BlueprintCallable, Category = "Game Over")
		void GameOverTimeFreezed();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
		AMain* MainPlayer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
		UWorld* CurrentWorld;

	
	FTimerHandle BulletTimeTimer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
		float BulletTimeDuration = 5.0f;

	// specific stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
		float NormalTimeDilation = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
		float TimeDilationMultiplier = 0.75f;

public:	
	virtual void ActivateAbilityEffect(UData_AbilityRequiredInfo* requiredInfo) override;
};
