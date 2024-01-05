// Fill out your copyright notice in the Description page of Project Settings.


#include "CalmComponent.h"

// Sets default values for this component's properties
UCalmComponent::UCalmComponent() {
}

bool UCalmComponent::isInMaxCalm() {
	return calm >= maxCalm;
}

void UCalmComponent::SetCalm(float calmAmount) {
	calm = calmAmount;
}
float UCalmComponent::GetCalm(){
	return calm;
}
void UCalmComponent::SetMaxCalm(float maxCalmAmount){
	maxCalm = maxCalmAmount;
}
float UCalmComponent::GetMaxCalm(){
	return maxCalm;
}

// to UI the percentage
float UCalmComponent::GetCalmPercentage(){
	return calm / maxCalm;
}

// update character frenzy value
void UCalmComponent::UpdateCalm(float modifier){
	if (!isInMaxCalm()) {
		calm += modifier;

		if (calm < 0) {
			calm = 0;
		}
	}
	else {
		calm = maxCalm;
	}
}

void UCalmComponent::UpdateMaxCalm(float modifier) {
	maxCalm += modifier;
}

float UCalmComponent::UseAllCalm() {
	float aux = calm;
	calm = 0.0f;
	return aux;
}