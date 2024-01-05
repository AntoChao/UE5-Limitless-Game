// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Common_Enums.h"
#include "FloatingNumberActor.generated.h"

UCLASS()
class LIMITLESS_API AFloatingNumberActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloatingNumberActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Self Destroy")
		FTimerHandle SelfDestoyTimer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Self Destroy")
		float SelfDestoyDuration = 5.0f;

	UFUNCTION(BlueprintCallable, Category = "Self Destroy")
		void SelfDestroyTimer();


public:	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Set Float Number")
		void SetDamageNumber(float damage);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Set Float Number")
		void SetDamagePercentage(float percentage);

};
