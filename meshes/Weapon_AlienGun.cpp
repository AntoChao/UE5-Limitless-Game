// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon_AlienGun.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Components/BoxComponent.h"
#include "../All_Enemies/EnemyClass.h"

// Sets default values
AWeapon_AlienGun::AWeapon_AlienGun()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Body = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponBody"));
	Body->SetOnlyOwnerSee(false);
	Body->SetupAttachment(CollisionComp);
	Body->bCastDynamicShadow = false;
	Body->CastShadow = false;
	Body->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
}

// Called when the game starts or when spawned
void AWeapon_AlienGun::BeginPlay()
{
	Super::BeginPlay();

	beingUsed = false;
	OwnByMain = true;
}