// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneralDecalActor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGeneralDecalActor::AGeneralDecalActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGeneralDecalActor::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(SelfDestroyTimer, this,
		&AGeneralDecalActor::SelfDestruction, lifeSpan, true);

}

// Called every frame
void AGeneralDecalActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGeneralDecalActor::SelfDestruction()
{
	Destroy();
}