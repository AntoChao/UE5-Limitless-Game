// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability_Sum_MomFoot.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Engine/EngineTypes.h"
#include "Engine/Blueprint.h"
#include "DrawDebugHelpers.h"
#include "Math/Vector.h"
#include "../meshes/Weapon_MomFoot.h"
#include "../AllCharactersClass.h"

// Sets default values
AAbility_Sum_MomFoot::AAbility_Sum_MomFoot(const class FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAbility_Sum_MomFoot::BeginPlay()
{
	Super::BeginPlay();
}

bool AAbility_Sum_MomFoot::AbilityRequirement(UData_AbilityRequiredInfo* requiredInfo)
{
	if (requiredInfo->GetPlayerFrenzy() >= FrenzyCost->GetFrenzy() && ShotTheLineTraceCheck(requiredInfo->GetHitResult().ImpactPoint))
	{
		// GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("USING Mom Foot"));
		// have to hit a enemy as it is a "projectile"
		/*
		if (requiredInfo->GetHitResult().GetActor()->GetClass()->IsChildOf(AEnemyClass::StaticClass()))
		{
			return true;
		}
		else
		{
			return false;
		}
		*/
		return true;
	}
	else
	{
		return true;
	}
}


// unfinished
bool AAbility_Sum_MomFoot::ShotTheLineTraceCheck(FVector HitLocation)
{
	FComponentQueryParams DefaultComponentQueryParams;
	FCollisionResponseParams DefaultResponseParam;

	FVector Start = HitLocation;
	FVector End = HitLocation + FVector(0.0f, 0.0f, MomFootHeight);

	GetWorld()->LineTraceSingleByChannel(LineTraceHit, HitLocation, End, ECC_Visibility, DefaultComponentQueryParams, DefaultResponseParam);

	return true;
}

/*  ActivateAbilityEffect has 3 process
*	Customize ability stats
*	Do the effect
*	Calculate feedback in order to return -> override all calculution base on ability
*/
void AAbility_Sum_MomFoot::ActivateAbilityEffect(UData_AbilityRequiredInfo* requiredInfo)
{
	// Ability Effect -> Spawn the grenade in hand and manipulate the character to throw and release
	SpawnFoot(requiredInfo);

	// Calculate the feedback -> override all calculation -> the calculation is done after receive the decision
	// freCost, freReward, cocost, coReward, moveSpeedRew, Xp
}

/*
1: Get the result position, shot a line trace to top
2: if the LineTrace got block, get distance size, if the distance size is not enough -> reject the ability
3: if the LineTrace not got block-> spawn it and smash the position
*/
void AAbility_Sum_MomFoot::SpawnFoot(UData_AbilityRequiredInfo* requiredInfo)
{
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	MomFoot = requiredInfo->GetWorldPointer()->SpawnActor<AWeapon_MomFoot>(requiredInfo->GetPlayer()->GetMomFootClass(),
			(requiredInfo->GetHitResult().Location + FVector(0.0f, 0.0f, 5000.0f)),
			FRotator(0.0f, 0.0f, 0.0f), ActorSpawnParams);

	MomFoot->SetTargetLocation(requiredInfo->GetHitResult().ImpactPoint);
	MomFoot->SetMainController(requiredInfo->GetPlayer()->GetMainController());
	MomFoot->SetDamage(100.0f);
	MomFoot->SetbNormalFire(5000.0f, true);
}