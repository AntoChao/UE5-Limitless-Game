// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability_Shotgun.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Engine/EngineTypes.h"
#include "Engine/Blueprint.h"
#include "DrawDebugHelpers.h"
#include "../All_Enemies/EnemyClass.h"
#include "Math/Vector.h"
#include "../AllCharactersClass.h"
#include "../Main.h"

// Sets default values
AAbility_Shotgun::AAbility_Shotgun(const class FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAbility_Shotgun::BeginPlay()
{
	Super::BeginPlay();

}

// Define its requirement
bool AAbility_Shotgun::AbilityRequirement(UData_AbilityRequiredInfo* requiredInfo)
{
	// GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("USING SHOTGUN"));
	return true;
}

void AAbility_Shotgun::ActivateAbilityEffect(UData_AbilityRequiredInfo* requiredInfo)
{
	// do the effect
	if (IsValid(requiredInfo->GetHitResult().GetActor()))
	{
		// will give error if somehow the traceline hits the main and not the enemy
		if (requiredInfo->GetHitResult().GetActor()->GetClass()->IsChildOf(AEnemyClass::StaticClass()))
		{
			AEnemyClass* EnemyDelta = Cast<AEnemyClass>(requiredInfo->GetHitResult().GetActor());

			ApplyDamageToEnemy(EnemyDelta, CalculateSpecialDamage(requiredInfo), requiredInfo);
		}
	}

	// Calculate the feedback -> override all calculation
	// freCost, freReward, cocost, coReward, moveSpeedRew, Xp
	//CalculateXP();
}

float AAbility_Shotgun::CalculateSpecialDamage(UData_AbilityRequiredInfo* requiredInfo)
{
	//DistanceVector = requiredInfo->GetPlayerLocation() - requiredInfo->GetHitResult().GetActorLocation();
	Distance = requiredInfo->GetHitResult().Distance / 100;//->Distance en meters

	float GeneralDamage = CalculateGeneralDamage(requiredInfo);
	// modify, just testing
	if (Distance < 10)
	{
		// TOO BUSTED -> NO WAY THIS CALCULATION
		return GeneralDamage * Distance;
	}
	else
		if (Distance < 30)
		{
			return GeneralDamage * (Distance * 0.5);
		}
		else
		{
			return GeneralDamage * (Distance * 0.2);
		}
}