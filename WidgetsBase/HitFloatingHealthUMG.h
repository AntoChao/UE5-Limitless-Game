// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../Common_Enums.h"

#include "HitFloatingHealthUMG.generated.h"

UCLASS()
class TRUEPROJECT2_API UHitFloatingHealthUMG : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display")
		FString FloatHealthText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display")
		EDamageColor DamageTextColor;

public:
	UFUNCTION(BlueprintCallable, Category = "Setter")
		void SetHealthText(FString TheText);
	
	UFUNCTION(BlueprintCallable, Category = "Setter")
		void SetDamageColor(EDamageColor AColor);

};
