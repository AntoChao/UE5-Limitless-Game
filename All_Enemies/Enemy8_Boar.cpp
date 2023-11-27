// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy8_Boar.h"
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

/*

*/
// Sets default values
AEnemy8_Boar::AEnemy8_Boar()
{
}

// Called when the game starts or when spawned
void AEnemy8_Boar::BeginPlay()
{
	Super::BeginPlay();
	
	// Inicialize all values
	InitCharacHealth(100.0f);
	
	SetRarity(EEnemyRarity::ENormal);

	GeneralDistance = 2000.0f;

	AbilityOneDistance = 1000.f;
	AbilityTwoDistance = 1000.f;

	Ability1Duration = 1.0f;
	Ability2Duration = 1.0f;

	MinHeight = 300.0f;
	MaxHeight = 350.0f;
	bFlyUp = true;

	FlySpeed = 900.0f;
	DashSpeed = 3000.0f;


}

void AEnemy8_Boar::CustomTickFunction()
{
	Super::CustomTickFunction();
	
	if (GetActorLocation().Z <= LimitHeight)
	{
		bFlyUp = true;
	}
	else
	{
		bFlyUp = false;
	}

	FString miau = FString::SanitizeFloat(CharacterSpeed);
	GEngine->AddOnScreenDebugMessage(-1, 2.0, FColor::Red, *miau);

	/*
	if (IsAbleToUseAbility1())
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, TEXT("Able to use Ability 1"));
	}
	if (IsAbleToUseAbility2())
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, TEXT("Able to use Ability 2"));
	}
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, TEXT("----------------------"));
	*/

}

bool AEnemy8_Boar::IsAbleToUseAbility1()
{
	return AttackDirection.Size() <= AbilityOneDistance;
}
bool AEnemy8_Boar::IsAbleToUseAbility2()
{
	return AttackDirection.Size() <= AbilityTwoDistance;
}

/*
* Dash Attack, should create a collition or enable the collision around bird, and deal damage
*/
void AEnemy8_Boar::Ability1()
{
	Super::Ability1();
	// ApplyMoveSpeedBoost(5.0f);
	PlayAnimAbilityOne();
}

void AEnemy8_Boar::Ability1Finished()
{
	Super::Ability1Finished();
}

void AEnemy8_Boar::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp,
	class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Is Colliding with main"));
	
	if (IsUsingAbility1)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Is Using Ability 1"));
		if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
		{
			
			// if (OtherActor->GetClass()->IsChildOf(AAllCharactersClass::StaticClass()))
			if (OtherActor->IsA(AMain::StaticClass()))
			{
				// Apply damage
				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Should Apply Damage"));
				ApplyDamageToMain(EnemyBaseDamage);
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Should Not Apply Damage"));
			}
		}
	}
}

void AEnemy8_Boar::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp,
	class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	// nothing
}

void AEnemy8_Boar::Ability2()
{
	Super::Ability2();
	
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Using Ability 2"));

	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	CalculateAbility2Stats();
}

void AEnemy8_Boar::CalculateAbility2Stats()
{
	InitLocation1 = SelfPosition + FVector(50.0f, 50.0f, 0.0f);
	InitLocation2 = SelfPosition + FVector(50.0f, -50.0f, 0.0f);
}
