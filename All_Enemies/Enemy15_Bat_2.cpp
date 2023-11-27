// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy15_Bat_2.h"
#include "Engine/EngineTypes.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "../components/HealthComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"
#include "../Main.h"

// Sets default values
AEnemy15_Bat_2::AEnemy15_Bat_2()
{
}

// Called when the game starts or when spawned
void AEnemy15_Bat_2::BeginPlay()
{
	Super::BeginPlay();
	
	// Inicialize all values
	InitCharacHealth(100.0f);
	
	SetRarity(EEnemyRarity::ENormal);
}

bool AEnemy15_Bat_2::IsAbleToUseAbility1()
{
	FString miau = FString::SanitizeFloat(AttackDirection.Size());
	GEngine->AddOnScreenDebugMessage(-1, 2.0, FColor::Red, *miau);

	return AttackDirection.Size() <= AbilityOneDistance;
	
}
bool AEnemy15_Bat_2::IsAbleToUseAbility2()
{
	return AttackDirection.Size() <= AbilityTwoDistance;
}

/*
* Dash Attack, should create a collition or enable the collision around bird, and deal damage
*/
void AEnemy15_Bat_2::Ability1()
{
	Super::Ability1();
	ReceiveSpeedBoost(5.0f, 5.0f);
	PlayAnimAbilityOne();
}

void AEnemy15_Bat_2::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp,
	class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsUsingAbility1)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Is Using Ability 1"));
		if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
		{
			
			if (OtherActor->IsA(AMain::StaticClass()))
			{
				// Apply damage
				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Should Apply Damage"));
				ApplyDamageToMain(5.0f);
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Should Not Apply Damage"));
			}
		}
	}
}

void AEnemy15_Bat_2::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp,
	class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	// nothing
}

void AEnemy15_Bat_2::Ability2()
{
	Super::Ability2();
	ApplyDamageToMain(10.0f);
}

