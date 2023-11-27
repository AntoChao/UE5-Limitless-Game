// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthBarActor.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "../Main.h"

// Sets default values
AHealthBarActor::AHealthBarActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHealthBarActor::BeginPlay()
{
	Super::BeginPlay();
}