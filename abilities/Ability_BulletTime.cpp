// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability_BulletTime.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Engine/EngineTypes.h"
#include "Engine/Blueprint.h"
#include "DrawDebugHelpers.h"
#include "../All_Enemies/EnemyClass.h"
#include "Math/Vector.h"
#include "../AllCharactersClass.h"
#include "../Main.h"

// Sets default values
AAbility_BulletTime::AAbility_BulletTime(const class FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAbility_BulletTime::BeginPlay()
{
	Super::BeginPlay();
}

// Define its requirement
bool AAbility_BulletTime::AbilityRequirement(UData_AbilityRequiredInfo* requiredInfo)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("USING BulletTime"));
	return true;
}

// WHAT HAPPEND IF THE PLAYER USE THE ABILITY MULTI TIMES
void AAbility_BulletTime::ActivateAbilityEffect(UData_AbilityRequiredInfo* requiredInfo)
{
	
	// do the effect
	if (requiredInfo->GetWorldPointer() != nullptr)
	{
		if (requiredInfo->GetPlayer() != nullptr)
		{
			CurrentWorld = requiredInfo->GetWorldPointer();
			MainPlayer = requiredInfo->GetPlayer();

			// Set the desired time dilation
			CurrentTimeDilation = CurrentTimeDilation * TimeDilationMultiplier;
			CurrentWorld->GetWorldSettings()->SetTimeDilation(CurrentTimeDilation);
			// Set the player time dilation to normal
			MainPlayer->CustomTimeDilation = 1 / CurrentTimeDilation;

			// if the bullet time niagara is still NOT spawned yet
			if (!MainPlayer->GetIsBulletTimeNiagaraSpawned())
			{
				MainPlayer->AttachBulletTimeNiagara();
				MainPlayer->SetIsBulletTimeNiagaraSpawned(true);
			}
		
			// run a timer to turn back the time dilation
			BulletTimeDuration = BulletTimeDuration * CurrentTimeDilation;
			CurrentWorld->GetTimerManager().SetTimer(BulletTimeTimer, this,
				&AAbility_BulletTime::ResetTimeDilation, BulletTimeDuration, true);

			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("japishjapish"));

		}
	}
	
	// Calculate the feedback -> override all calculation
	// freCost, freReward, cocost, coReward, moveSpeedRew, Xp
}

void AAbility_BulletTime::ResetTimeDilation()
{
	if (IsValid(CurrentWorld))
	{
		if (IsValid(MainPlayer))
		{
			CurrentWorld->GetWorldSettings()->SetTimeDilation(NormalTimeDilation);
			MainPlayer->CustomTimeDilation = NormalTimeDilation;

			CurrentTimeDilation = NormalTimeDilation;

			// if the bullet time niagara is spawned
			if (MainPlayer->GetIsBulletTimeNiagaraSpawned())
			{
				MainPlayer->DestroyBulletTimeNiagara();
				MainPlayer->SetIsBulletTimeNiagaraSpawned(false);
			}
		}
	}
}
