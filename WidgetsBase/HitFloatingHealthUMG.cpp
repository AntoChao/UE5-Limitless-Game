// Fill out your copyright notice in the Description page of Project Settings.


#include "HitFloatingHealthUMG.h"
#include "Components/ProgressBar.h"

void UHitFloatingHealthUMG::SetHealthText(FString TheText)
{
	FloatHealthText = TheText;
}

void UHitFloatingHealthUMG::SetDamageColor(EDamageColor AColor)
{
	DamageTextColor = AColor;
}
