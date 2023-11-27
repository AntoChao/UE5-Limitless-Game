// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability_Sniper.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Engine/EngineTypes.h"
#include "Engine/Blueprint.h"
#include "DrawDebugHelpers.h"
#include "../All_Enemies/EnemyClass.h"
#include "Math/Vector.h"
#include "../AllCharactersClass.h"
#include "../Main.h"

// Sets default values
AAbility_Sniper::AAbility_Sniper(const class FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAbility_Sniper::BeginPlay()
{
	Super::BeginPlay();

}

// Define its requirement
bool AAbility_Sniper::AbilityRequirement(UData_AbilityRequiredInfo* requiredInfo)
{
	// requirement->exist an enemy to hit
		// Do damage to all allcaharacterclass child
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("USING Sniper"));
	return true;
}

void AAbility_Sniper::ActivateAbilityEffect(UData_AbilityRequiredInfo* requiredInfo)
{
	// do the effect
	if (IsValid(requiredInfo->GetHitResult().GetActor()))
	{
		if (requiredInfo->GetHitResult().GetActor()->GetClass()->IsChildOf(AEnemyClass::StaticClass()))
		{
			AEnemyClass* EnemyDelta = Cast<AEnemyClass>(requiredInfo->GetHitResult().GetActor());

			ApplyDamageToEnemy(EnemyDelta, CalculateSpecialDamage(requiredInfo), requiredInfo);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("enemy no character class"));
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("enemy no valid"));
	}
	
	//requiredInfo->GetEnemyTargetClass()->GetHitten(Damage->GetDamage());

	// Calculate the feedback -> override all calculation
	// freCost, freReward, cocost, coReward, moveSpeedRew, Xp
}

float AAbility_Sniper::CalculateSpecialDamage(UData_AbilityRequiredInfo* requiredInfo)
{
	//DistanceVector = requiredInfo->GetPlayerLocation() - requiredInfo->GetHitResult().GetActorLocation();
	Distance = requiredInfo->GetHitResult().Distance / 100;//->Distance en meters
	float GeneralDamage = CalculateGeneralDamage(requiredInfo);

	// modify, just testing
	if (Distance > 100)
	{
		return GeneralDamage * Distance;
	}
	else
		if (Distance > 40)
		{
			return GeneralDamage * (Distance * 0.7);
		}
		else
		{
			return GeneralDamage * (Distance * 0.4);
		}
}
