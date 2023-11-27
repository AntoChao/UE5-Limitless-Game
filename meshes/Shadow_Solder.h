// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Shadow_Solder.generated.h"

UCLASS()
class TRUEPROJECT2_API AShadow_Solder : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShadow_Solder();
	
	/*
	Just a bp which contain:
	- shadow solder Skeleton 
	- its animation
	*/
	
	/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category = "Body")
		class USkeletalMeshComponent* BodyComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
