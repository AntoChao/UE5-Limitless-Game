// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon_SniperRifle.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Components/BoxComponent.h"
#include "../All_Enemies/EnemyClass.h"

// Sets default values
AWeapon_SniperRifle::AWeapon_SniperRifle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Body = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("EnemyBody"));
	Body = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponBody"));
	Body->SetOnlyOwnerSee(false);
	Body->SetupAttachment(CollisionComp);
	Body->bCastDynamicShadow = false;
	Body->CastShadow = false;
	Body->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
}

// Called when the game starts or when spawned
void AWeapon_SniperRifle::BeginPlay()
{
	Super::BeginPlay();

	beingUsed = false;
	OwnByMain = true;
}

/* to think about -> should be the fire gun do damage or the ability
void AWeapon_Blade::DoDamage()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("Doing Damage to enemy"));

	UGameplayStatics::ApplyPointDamage(Enemy, 10.0f, GetActorLocation(), MyHit, nullptr, this, NULL);
}
*/