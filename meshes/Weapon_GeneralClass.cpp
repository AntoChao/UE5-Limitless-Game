// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon_GeneralClass.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "../Main.h"
#include "../MainController.h"
#include "../Enemies_Controller/AIEnemyClassController.h"
#include "Math/UnrealMathUtility.h"
#include "../All_Enemies/EnemyClass.h"

// Sets default values
AWeapon_GeneralClass::AWeapon_GeneralClass()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DamageComponent = CreateDefaultSubobject<UDamageComponent>(TEXT("Damage"));
}

// Called when the game starts or when spawned
void AWeapon_GeneralClass::BeginPlay()
{
	Super::BeginPlay();

	// lifespan variables
	LifeSpan = 0.0f;

	MainController = nullptr;
	EnemyController = nullptr;
}

// Called every frame
void AWeapon_GeneralClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeapon_GeneralClass::CustomTickFunction()
{
	GetWorldTimerManager().SetTimer(TickSimulatorTimer, this,
		&AWeapon_GeneralClass::CustomTickFunction, TickSimulateTime, true);

	// the things to do
}

bool AWeapon_GeneralClass::WeaponOwnedByMain()
{
	return OwnByMain;
}

void AWeapon_GeneralClass::SetMainController(AMainController* AMainController)
{
	MainController = AMainController;
}
void AWeapon_GeneralClass::SetEnemyController(AAIEnemyClassController* AEnemyController)
{
	EnemyController = AEnemyController;
}

// No logic, each weapon is totally different
void AWeapon_GeneralClass::DoDamage()
{
	return;
}

void AWeapon_GeneralClass::isUsingWeapon(bool modifier)
{
	beingUsed = modifier;
}

void AWeapon_GeneralClass::StartDieTimer()
{
	GetWorldTimerManager().SetTimer(LifeSpanTimer, this,
		&AWeapon_GeneralClass::DieEffect, LifeSpan, false);
}

void AWeapon_GeneralClass::DieEffect()
{
	PlayEndAnimation();
	
	// destroy may not be part of die effect.
	// Destroy();
}

void AWeapon_GeneralClass::Die()
{
	Destroy();
}

void AWeapon_GeneralClass::SetDamage(float aDamageValue)
{
	DamageComponent->SetDamage(aDamageValue);
}

void AWeapon_GeneralClass::PlaySpawnAnimation()
{
	UAnimInstance* AnimInstance = Body->GetAnimInstance();

	if (AnimInstance)
	{
		if (IsValid(AnimMontage_SpawnEffect))
		{
			AnimInstance->Montage_Play(AnimMontage_SpawnEffect, 1.0f);

			// Bind the OnMontageEnded event to a custom function
			AnimInstance->OnMontageEnded.AddDynamic(this, &AWeapon_GeneralClass::OnSpawnMontageEnded);
		}
	}
}

void AWeapon_GeneralClass::OnSpawnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	return;
}

void AWeapon_GeneralClass::PlayEndAnimation()
{
	UAnimInstance* AnimInstance = Body->GetAnimInstance();

	if (AnimInstance)
	{
		if (IsValid(AnimMontage_DieEffect))
		{
			AnimInstance->Montage_Play(AnimMontage_DieEffect, 1.0f);

			// Bind the OnMontageEnded event to a custom function
			AnimInstance->OnMontageEnded.AddDynamic(this, &AWeapon_GeneralClass::OnDieMontageEnded);
		}
	}
}

// USE the bInterrupted parameter
void AWeapon_GeneralClass::OnDieMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (bInterrupted)
	{
		Destroy();
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Die Montage Got Interrupted"));
	}
	else
	{
		Destroy();
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Die Montage Did not Got Interrupted"));

	}
}