// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy11_Robot_Executor.h"
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
AEnemy11_Robot_Executor::AEnemy11_Robot_Executor()
{
}

// Called when the game starts or when spawned
void AEnemy11_Robot_Executor::BeginPlay()
{
	Super::BeginPlay();
	
	// Inicialize all values
	InitCharacHealth(300.0f);
	
	SetRarity(EEnemyRarity::ENormal);
}

bool AEnemy11_Robot_Executor::IsAbleToUseAbility1()
{
	FString miau = FString::SanitizeFloat(AttackDirection.Size());
	GEngine->AddOnScreenDebugMessage(-1, 2.0, FColor::Red, *miau);

	return AttackDirection.Size() <= AbilityOneDistance;
	
}
bool AEnemy11_Robot_Executor::IsAbleToUseAbility2()
{
	return AttackDirection.Size() <= AbilityTwoDistance;
}

void AEnemy11_Robot_Executor::Ability1()
{
	Super::Ability1();
	ReceiveSpeedBoost(5.0f, 5.0f);
	PlayAnimAbilityOne();
}
void AEnemy11_Robot_Executor::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp,
	class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsUsingAbility1)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Is Using Ability 1"));
		if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
		{
			
			if (OtherActor->GetClass()->IsChildOf(AAllCharactersClass::StaticClass()))
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

void AEnemy11_Robot_Executor::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp,
	class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	// nothing
}

void AEnemy11_Robot_Executor::Ability2()
{
	Super::Ability2();
	ApplyDamageToMain(10.0f);
}

