// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon_Missile.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "DrawDebugHelpers.h"
#include "../Main.h"
#include "../All_Enemies/EnemyClass.h"

// Sets default values
AWeapon_Missile::AWeapon_Missile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	CollisionComp->SetupAttachment(GetCapsuleComponent());
	// RootComponent = CollisionComp;

	// overlap event
	CollisionComp->OnComponentBeginOverlap.AddUniqueDynamic(this, &AWeapon_Missile::OnOverlapBegin);
	CollisionComp->OnComponentEndOverlap.AddUniqueDynamic(this, &AWeapon_Missile::OnOverlapEnd);

	//Body = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("EnemyBody"));
	Body = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Body"));
	Body->SetOnlyOwnerSee(false);
	Body->SetupAttachment(CollisionComp);
	Body->bCastDynamicShadow = false;
	Body->CastShadow = false;
	Body->SetRelativeLocation(FVector(0.f, 0.f, 0.f));

	StartFireSpline1 = CreateDefaultSubobject<USplineComponent>(TEXT("StartSpline1"));
	StartFireSpline1->SetupAttachment(GetCapsuleComponent());

	StartFireSpline2 = CreateDefaultSubobject<USplineComponent>(TEXT("StartSpline2"));
	StartFireSpline2->SetupAttachment(GetCapsuleComponent());

	ReCalculateSpline1 = CreateDefaultSubobject<USplineComponent>(TEXT("ReCalculateSpline1"));
	ReCalculateSpline1->SetupAttachment(GetCapsuleComponent());

	ReCalculateSpline2 = CreateDefaultSubobject<USplineComponent>(TEXT("ReCalculateSpline2"));
	ReCalculateSpline2->SetupAttachment(GetCapsuleComponent());
}

// Called when the game starts or when spawned
void AWeapon_Missile::BeginPlay()
{
	Super::BeginPlay();

	StartSplines.Add(StartFireSpline1);
	StartSplines.Add(StartFireSpline2);
	ReCalculateSplines.Add(ReCalculateSpline1);
	ReCalculateSplines.Add(ReCalculateSpline2);

	beingUsed = false;
	OwnByMain = false;
	// BaseDamage = 5.0f;

	ReFireDistance = 100.0f;

	// GetCharacterMovement()->MaxWalkSpeed = FlyingSpeed;
	ChaseParameter = false;

	bStartingFire = false;
	bReCalculatingPath = false;

	/*
	// some weapons need to add these in begin play and override custom tick
	TickSimulateTime = 0.1f;
	CustomTickFunction();
	*/

	LifeSpan = 10.0f;
	StartDieTimer();

}

void AWeapon_Missile::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp,
	class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		// if (OtherActor->GetClass()->IsChildOf(AAllCharactersClass::StaticClass()))
		if (OtherActor->IsA(AMain::StaticClass()))
		{
			// GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Collide with main"));

			Main = Cast<AMain>(OtherActor);

			if (IsValid(Main) && !Main->isMainDetecting())
			{
				DieEffect();
			}

			// Destroy();
		}
	}

}

void AWeapon_Missile::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp,
	class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	// nothing
}

// should override dodamage -> apply radial damage
void AWeapon_Missile::DoDamage(AActor* Actor)
{
	// need to test, some how it deal multiple damage to main
	
	UGameplayStatics::ApplyRadialDamage(
		GetWorld(),
		DamageComponent->GetDamage(),
		CollisionLocation,
		ExplotionRadius,
		UDamageType::StaticClass(),
		{},
		this,
		GetController(),
		false,
		ECollisionChannel::ECC_Visibility);
}

void AWeapon_Missile::DieEffect()
{
	// PlayEndAnimation();

	DoDamage(Target);
	MissileDieEffect();

}