// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "GeneralDecalActor.generated.h"

UCLASS()
class TRUEPROJECT2_API AGeneralDecalActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGeneralDecalActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Self Destroy
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Decal Actor")
		float lifeSpan = 5.0f;

	FTimerHandle SelfDestroyTimer;

	UFUNCTION(BlueprintCallable, Category = "Self Destruction")
		void SelfDestruction();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
