// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon_Blade.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "DrawDebugHelpers.h"
#include "../All_Enemies/EnemyClass.h"

// Sets default values
AWeapon_Blade::AWeapon_Blade()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Use a sphere as a simple collision representation

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	CollisionComp->BodyInstance.SetCollisionProfileName("HitBox");

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;
	
	// Set as root component
	RootComponent = CollisionComp;

	Body = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponBody"));
	Body->SetOnlyOwnerSee(false);
	Body->SetupAttachment(CollisionComp);
	Body->bCastDynamicShadow = false;
	Body->CastShadow = false;
	Body->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
}

// Called when the game starts or when spawned
void AWeapon_Blade::BeginPlay()
{
	Super::BeginPlay();
	
	// overlap event
	CollisionComp->OnComponentBeginOverlap.AddUniqueDynamic(this, &AWeapon_Blade::OnOverlapBegin);
	CollisionComp->OnComponentEndOverlap.AddUniqueDynamic(this, &AWeapon_Blade::OnOverlapEnd);
	
	beingUsed = false;
	OwnByMain = true;
}

void AWeapon_Blade::usingBlade(bool modifier)
{
	if (modifier)
	{
		EnemyHitten = {};
	}
	beingUsed = modifier;
}

TSet<AActor*> AWeapon_Blade::ReturnHittenEnemies()
{
	return EnemyHitten;
}

void AWeapon_Blade::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp,
	class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{	
	if (beingUsed)
	{
		if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
		{
			if (OtherActor->GetClass()->IsChildOf(AEnemyClass::StaticClass()))
			{
				//Enemy = Cast<ABasicEnemy>(OtherActor);
				//GetOverlappingActors(EnemyHitten, AEnemyClass::StaticClass());
				if (EnemyHitten.Contains(OtherActor))
				{
					GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("the enemy is already hitten miaumiaumiau miaumiaumiau"));
				}
				else
				{
					EnemyHitten.Add(OtherActor);
					GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("the enemy is not hitten before"));
				}
			}
		}
	}
}

void AWeapon_Blade::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp,
	class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	// nothing
}

void AWeapon_Blade::DoDamage(AActor* Actor)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("Doing Damage to enemy"));

	UGameplayStatics::ApplyPointDamage(Enemy, 10.0f, GetActorLocation(), MyHit, nullptr, nullptr, NULL);
}