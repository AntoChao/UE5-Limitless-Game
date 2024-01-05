// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatingNumberActor.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "../Main.h"

// Sets default values
AFloatingNumberActor::AFloatingNumberActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFloatingNumberActor::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(SelfDestoyTimer, this,
		&AFloatingNumberActor::SelfDestroyTimer, SelfDestoyDuration, true);
}

void AFloatingNumberActor::SelfDestroyTimer()
{
	Destroy();
}