// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CalmComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LIMITLESS_API UCalmComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCalmComponent();

protected:
	float calm = 0.0f;
	float maxCalm = 100.0f;

	bool isInMaxCalm();

public:
	// setters and getters, can be stats/ cost/ reward
	void SetCalm(float calmAmount);
	float GetCalm();
	void SetMaxCalm(float maxCalmAmount);
	float GetMaxCalm();

	// to UI the percentage
	float GetCalmPercentage();

	// update character frenzy value
	void UpdateCalm(float modifier);
	void UpdateMaxCalm(float modifier);
	float UseAllCalm();
};
