// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability_BasicPistol.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Engine/EngineTypes.h"
#include "Engine/Blueprint.h"
#include "DrawDebugHelpers.h"
#include "Math/Vector.h"
#include "../AllCharactersClass.h"
#include "../Main.h"

// Sets default values
AAbility_BasicPistol::AAbility_BasicPistol(const class FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// feedBackContainer = NewObject<UData_AbilityFeedBackInfo>();
}

// Called when the game starts or when spawned
void AAbility_BasicPistol::BeginPlay()
{
	Super::BeginPlay();
}

// Define its requirement
// Pistol should always be able to fire, no limit
bool AAbility_BasicPistol::AbilityRequirement(UData_AbilityRequiredInfo* requiredInfo)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("USING PISTOL"));
	return true;
}

/*ActivateAbilityEffect has 3 process
*	Customize ability stats
*	Do the effect
*	Calculate feedback in order to return -> override all calculution base on ability
*/
void AAbility_BasicPistol::ActivateAbilityEffect(UData_AbilityRequiredInfo* requiredInfo)
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
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("enemy no character class"));
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("enemy no valid"));
	}
	
	// Calculate the feedback -> override all calculation
	// freCost, freReward, cocost, coReward, moveSpeedRew, Xp
}

float AAbility_BasicPistol::CalculateSpecialDamage(UData_AbilityRequiredInfo* requiredInfo)
{
	//DistanceVector = requiredInfo->GetPlayerLocation() - requiredInfo->GetHitResult().GetActorLocation();
	Distance = requiredInfo->GetHitResult().Distance / 100;//->Distance en meters

	float GeneralDamage = CalculateGeneralDamage(requiredInfo);

	if (Distance < 20)
	{
		return GeneralDamage * 1;
	}
	else
	{
		if (Distance < 40)
		{
			return GeneralDamage * 0.8;
		}
		else
		{
			return GeneralDamage * 0.5;
		}
	}
}