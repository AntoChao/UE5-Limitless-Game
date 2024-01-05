// Fill out your copyright notice in the Description page of Project Settings.


#include "HitFloatingHealthUMG.h"
#include "Math/UnrealMath.h"
#include "Components/ProgressBar.h"

void UHitFloatingHealthUMG::SetHealthText(FString TheText) {
	FloatHealthText = TheText;
}

void UHitFloatingHealthUMG::LerpDamageColor(float Percentage) {
    Percentage = FMath::Clamp(Percentage, 0.0f, 1.0f);

    // Define the start color (white) and the end color (red)
    FLinearColor StartColor = FLinearColor::White;
    FLinearColor EndColor = FLinearColor::Red;
    /*
    FString perlerp = FString::Printf(TEXT("Health UMG lerp color percentage: %f"), Percentage);
    GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, perlerp);*/

    // Interpolate between the start and end colors based on the percentage
    DamageTextColor = FMath::Lerp(StartColor, EndColor, Percentage);
}