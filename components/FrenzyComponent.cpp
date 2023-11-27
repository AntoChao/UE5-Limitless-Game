// Fill out your copyright notice in the Description page of Project Settings.


#include "FrenzyComponent.h"

// Sets default values for this component's properties
UFrenzyComponent::UFrenzyComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFrenzyComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UFrenzyComponent::SetFrenzy(float frenzyAmount)
{
	frenzy = frenzyAmount;
}
float UFrenzyComponent::GetFrenzy()
{
	return frenzy;
}
void UFrenzyComponent::SetMaxFrenzy(float maxFrenzyAmount)
{
	maxFrenzy = maxFrenzyAmount;
}
float UFrenzyComponent::GetMaxFrenzy()
{
	return maxFrenzy;
}

// to UI the percentage
float UFrenzyComponent::GetFrenzyPercentage()
{
	return frenzy / maxFrenzy;
}

// update character frenzy value
void UFrenzyComponent::UpdateFrenzy(float modifier)
{
	frenzy += modifier;
}

void UFrenzyComponent::UpdateMaxFrenzy(float modifier)
{
	maxFrenzy += modifier;
}