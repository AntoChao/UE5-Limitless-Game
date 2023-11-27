// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon_BlackHoleBomb.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "DrawDebugHelpers.h"
#include "../Main.h"
#include "../All_Enemies/EnemyClass.h"

#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
AWeapon_BlackHoleBomb::AWeapon_BlackHoleBomb()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	CollisionComp->SetupAttachment(GetCapsuleComponent());
	// RootComponent = CollisionComp;

	//Body = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("EnemyBody"));
	Body = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Body"));
	Body->SetOnlyOwnerSee(false);
	Body->SetupAttachment(CollisionComp);
	Body->bCastDynamicShadow = false;
	Body->CastShadow = false;
	Body->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	
	// Use a sphere as a simple collision representation
	EffectArea = CreateDefaultSubobject<USphereComponent>(TEXT("BlackHole Area"));
	EffectArea->SetupAttachment(CollisionComp);
}

// Called when the game starts or when spawned
void AWeapon_BlackHoleBomb::BeginPlay()
{
	Super::BeginPlay();

	EnemiesToPull = {};

	//beingUsed = false;
	// just for testing
	beingUsed = false;

	OwnByMain = true;
	
	LifeSpan = 5.0f;
	ReachOffSet = 100.0f;

	// Do not need die timer as it all respond by spawn animation
	// StartDieTimer();

	PlaySpawnAnimation();
}

void AWeapon_BlackHoleBomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeapon_BlackHoleBomb::CustomTickFunction()
{
	Super::CustomTickFunction();
}

void AWeapon_BlackHoleBomb::PullOverlappedEnemies()
{
	TArray<AActor*> OverlappingActors;
	EffectArea->GetOverlappingActors(OverlappingActors, AActor::StaticClass());
	for (AActor* OverlappingActor : OverlappingActors)
	{
		AEnemyClass* EnemyDelta = Cast<AEnemyClass>(OverlappingActor);
		if (EnemyDelta)
		{
			EnemiesToPull.Add(EnemyDelta);
			BlackHoleEffect(EnemyDelta);

			DrawDebugSphere
			(
				GetWorld(), EnemyDelta->GetActorLocation(), 100.0f, 10, FColor::Red, false, 5.0f, 2, 5.0f
			);
		}
	}
}
void AWeapon_BlackHoleBomb::BlackHoleEffect(AEnemyClass* AEnemy)
{
	// check if the enemy "valid"
	if (IsValid(AEnemy))
	{
		// ATTEMPT BY SET ACTOR LOCATION
		AEnemy->ReceiveSpecialStatus(ESpecialStatus::EForceMoveByTime,
			PullDuration, 0.0f, GetActorLocation());

	}
}

void AWeapon_BlackHoleBomb::DieEffect()
{
	Super::DieEffect();
	DoDamage();
}

// should override dodamage -> does not apply radial damage, just insta kill a small ridius enemies
void AWeapon_BlackHoleBomb::DoDamage()
{
	// Iterate through the actors and apply the pulling force
	for (AEnemyClass* AEnemy : EnemiesToPull)
	{
		// check if the enemy "valid"
		if (IsValid(AEnemy))
		{
			// check if enemy is normal or special, only one shot them
			if (AEnemy->GetRarity() == EEnemyRarity::ENormal || AEnemy->GetRarity() == EEnemyRarity::ESpecial)
			{
				// Apply the 100% kill damage or destroy it directly as it is so OP
				AEnemy->Destroy();
			}
		}
		else
		{
			// remove no valid enemies
			EnemiesToPull.Remove(AEnemy);
		}
	}
}

UProjectileMovementComponent* AWeapon_BlackHoleBomb::GetWeaponProjectileCompMovement()
{
	return ProjectileMovement;
}

USkeletalMeshComponent* AWeapon_BlackHoleBomb::GetWeaponSkeleton()
{
	return Body;
}

void AWeapon_BlackHoleBomb::ReachLocationEffect()
{
	// Stop the movement
	StopMoving();

	// turn back the physics
	//GetCapsuleComponent()->SetSimulatePhysics(true);
	PhysicsFunc();
}