// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeneralAbilityClass.h"
#include "AbilityTest.generated.h"

UCLASS()
class LIMITLESS_API AAbilityTest : public AGeneralAbilityClass
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAbilityTest(const class FObjectInitializer& ObjectInitializer);

public:	

	virtual void ActivateAbilityEffect(UData_AbilityRequiredInfo* requiredInfo) override;
};
