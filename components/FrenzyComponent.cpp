// Fill out your copyright notice in the Description page of Project Settings.


#include "FrenzyComponent.h"

// Sets default values for this component's properties
UFrenzyComponent::UFrenzyComponent(){
}
void UFrenzyComponent::SetFrenzy(float frenzyAmount) {
	frenzy = frenzyAmount;
}
float UFrenzyComponent::GetFrenzy() {
	return frenzy;
}
void UFrenzyComponent::SetMaxFrenzy(float maxFrenzyAmount) {
	maxFrenzy = maxFrenzyAmount;
}
float UFrenzyComponent::GetMaxFrenzy() {
	return maxFrenzy;
}

// to UI the percentage
float UFrenzyComponent::GetFrenzyPercentage() {
	return frenzy / maxFrenzy;
}

// update character frenzy value
void UFrenzyComponent::UpdateFrenzy(float modifier){
	frenzy += modifier;

	if (frenzy < 0) {
		frenzy = 0;
	}
}

void UFrenzyComponent::UpdateMaxFrenzy(float modifier){
	maxFrenzy += modifier;
}