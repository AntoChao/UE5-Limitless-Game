// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy1_Bird_WindSlash.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
AEnemy1_Bird_WindSlash::AEnemy1_Bird_WindSlash()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	//GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	// CollisionComp->SetupAttachment(GetCapsuleComponent());
	RootComponent = CollisionComp;

	// overlap event
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AEnemy1_Bird_WindSlash::OnOverlapBegin);
	CollisionComp->OnComponentEndOverlap.AddDynamic(this, &AEnemy1_Bird_WindSlash::OnOverlapEnd);


	//Body = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("EnemyBody"));
	Body = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponBody"));
	Body->SetOnlyOwnerSee(false);
	Body->SetupAttachment(CollisionComp);
	Body->bCastDynamicShadow = false;
	Body->CastShadow = false;
	Body->SetRelativeLocation(FVector(0.f, 0.f, 0.f));

	SlashRotation = FRotator(0.1f, 10.0f, 0.0f);
}

// Called when the game starts or when spawned
void AEnemy1_Bird_WindSlash::BeginPlay()
{
	Super::BeginPlay();

	Damage = 10.0f;

	CustomTickFunction();
	InitLocation = GetActorLocation();
}

void AEnemy1_Bird_WindSlash::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	PermaRotate();
}

void AEnemy1_Bird_WindSlash::CustomTickFunction()
{
	GetWorldTimerManager().SetTimer(TickSimulatorTimer, this,
		&AEnemy1_Bird_WindSlash::CustomTickFunction, TickSimulateTime, true);

	// PermaRotate();
}
/*
void AActor::K2_AddActorLocalRotation(FRotator DeltaRotation, bool bSweep, FHitResult& SweepHitResult, bool bTeleport)
{
	AddActorLocalRotation(DeltaRotation, bSweep, (bSweep ? &SweepHitResult : nullptr), TeleportFlagToEnum(bTeleport));
}
*/
void AEnemy1_Bird_WindSlash::PermaRotate()
{
	AddActorLocalRotation(SlashRotation);
	// SetActorRotation(SlashRotation);
}

void AEnemy1_Bird_WindSlash::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp,
	class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Wind Slash Is Colliding with main"));

	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		//if (OtherActor->GetClass()->IsChildOf(AAllCharactersClass::StaticClass()))
		if (OtherActor->IsA(AMain::StaticClass()))
		{
			Main = Cast<AMain>(OtherActor);
			DieEffect();
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("But it is not a main"));
		}
	}
}

void AEnemy1_Bird_WindSlash::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp,
	class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	// nothing
}