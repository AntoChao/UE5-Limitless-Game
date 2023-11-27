// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon_Bullet.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "DrawDebugHelpers.h"
#include "../Main.h"
#include "../All_Enemies/EnemyClass.h"

// Sets default values
AWeapon_Bullet::AWeapon_Bullet()
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
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AWeapon_Bullet::OnOverlapBegin);
	CollisionComp->OnComponentEndOverlap.AddDynamic(this, &AWeapon_Bullet::OnOverlapEnd);

	//Body = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("EnemyBody"));
	Body = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Body"));
	Body->SetOnlyOwnerSee(false);
	Body->SetupAttachment(CollisionComp);
	Body->bCastDynamicShadow = false;
	Body->CastShadow = false;
	Body->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
}

// Called when the game starts or when spawned
void AWeapon_Bullet::BeginPlay()
{
	Super::BeginPlay();

	beingUsed = false;
	// BaseDamage = 5.0f;
	ChaseParameter = false;
	OwnByMain = false;
}

void AWeapon_Bullet::CustomTickFunction()
{
	Super::CustomTickFunction();
	IfReachLocation();
}

void AWeapon_Bullet::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp,
	class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Is Colliding with main"));
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		// if (OtherActor->GetClass()->IsChildOf(AAllCharactersClass::StaticClass()))
		if (OtherActor->IsA(AMain::StaticClass()))
		{
			Main = Cast<AMain>(OtherActor);
			if (IsValid(Main) && !Main->isMainDetecting())
			{
				DoDamage();
				Destroy();
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Should Not Apply Damage"));
		}
	}
}

void AWeapon_Bullet::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp,
	class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	// nothing
}

void AWeapon_Bullet::ReachLocationEffect()
{
	Super::ReachLocationEffect();

	DieEffect();
}