// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthBarUMG.h"
#include "Components/ProgressBar.h"

void UHealthBarUMG::SetHealthPercentage(float Health)
{
	HealthPercentage = Health;
}