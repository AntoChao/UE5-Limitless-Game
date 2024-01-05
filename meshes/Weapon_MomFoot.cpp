// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon_MomFoot.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "DrawDebugHelpers.h"
#include "../Main.h"
#include "../All_Enemies/EnemyClass.h"

// Sets default values
AWeapon_MomFoot::AWeapon_MomFoot() {
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
}

// Called when the game starts or when spawned
void AWeapon_MomFoot::BeginPlay() {
	Super::BeginPlay();

	// overlap event
	CollisionComp->OnComponentBeginOverlap.AddUniqueDynamic(this, &AWeapon_MomFoot::OnOverlapBegin);

	beingUsed = false;
	OwnByMain = true;
	// BaseDamage = 5.0f;
	
	// Do not need die timer as it all respond by spawn animation
	// StartDieTimer();

	PlaySpawnAnimation();
}

void AWeapon_MomFoot::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp,
	class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr)) {
		//if (OtherActor->IsA(AMain::StaticClass()))
		if (OtherActor->GetClass()->IsChildOf(AEnemyClass::StaticClass())) {
			Enemy = Cast<AEnemyClass>(OtherActor);
			DoDamage(Enemy);
		}
	}
}

void AWeapon_MomFoot::ReachLocationEffect()
{
	Spawn_ReachLocationEffects();
}