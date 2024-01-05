// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon_ReverseProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "DrawDebugHelpers.h"
#include "../Main.h"
#include "../All_Enemies/EnemyClass.h"

// Sets default values
AWeapon_ReverseProjectile::AWeapon_ReverseProjectile() {
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
void AWeapon_ReverseProjectile::BeginPlay() {
	Super::BeginPlay();

	// overlap event
	CollisionComp->OnComponentBeginOverlap.AddUniqueDynamic(this, &AWeapon_ReverseProjectile::OnOverlapBegin);

	beingUsed = false;
	OwnByMain = true;
	// BaseDamage = 5.0f;

	// GetCharacterMovement()->MaxWalkSpeed = FlyingSpeed;
	ChaseParameter = true;

	bStartingFire = false;

	LifeSpan = 10.0f;
	StartDieTimer();
}

void AWeapon_ReverseProjectile::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	/*
	if (bNormalFire) { 
		NormalFire(DeltaTime);
	}

	UpdateLocationVariable();
	UpdateCollisionCompPosition();*/
}

void AWeapon_ReverseProjectile::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp,
	class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		// if (OtherActor->IsA(AMain::StaticClass()))
		if (OtherActor->GetClass()->IsChildOf(AEnemyClass::StaticClass()))
		{
			Enemy = Cast<AEnemyClass>(OtherActor);
			DieEffect();
		}
	}

}

// should override dodamage -> apply radial damage
void AWeapon_ReverseProjectile::DoDamage(AActor* Actor) {
	// need to test, some how it deal multiple damage to main
	
	UGameplayStatics::ApplyRadialDamage(
		GetWorld(),
		DamageComponent->GetDamage(),
		CollisionLocation,
		ExplotionRadius,
		UDamageType::StaticClass(),
		{},
		this,
		nullptr,
		false,
		ECollisionChannel::ECC_Visibility);
}

void AWeapon_ReverseProjectile::DieEffect() {
	Super::DieEffect();
	
	DoDamage(Target);
	
	Destroy();
}

void AWeapon_ReverseProjectile::ReachLocationEffect() {
	Destroy();
}