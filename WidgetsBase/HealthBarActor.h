// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Common_Enums.h"
#include "HealthBarActor.generated.h"

UCLASS()
class TRUEPROJECT2_API AHealthBarActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHealthBarActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Health Bar")
		void SetProgressPercentage(float percentage);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Display")
		void SetProgressBarVisibility(bool Visible);

};
