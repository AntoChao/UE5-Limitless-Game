// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../Common_Enums.h"

#include "HealthBarUMG.generated.h"

UCLASS()
class TRUEPROJECT2_API UHealthBarUMG : public UUserWidget
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display")
		float HealthPercentage;
	
public:
	UFUNCTION(BlueprintCallable, Category = "Setter")
		void SetHealthPercentage(float Health);

	// may not useful
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Display")
		void SetHealthBarVisibility(bool Visible);
};
