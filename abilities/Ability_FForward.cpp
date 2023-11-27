// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability_FForward.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Engine/EngineTypes.h"
#include "Engine/Blueprint.h"
#include "DrawDebugHelpers.h"
#include "../All_Enemies/EnemyClass.h"
#include "Math/Vector.h"
#include "../AllCharactersClass.h"
#include "../Main.h"

// Sets default values
AAbility_FForward::AAbility_FForward(const class FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAbility_FForward::BeginPlay()
{
	Super::BeginPlay();
}

// Define its requirement
bool AAbility_FForward::AbilityRequirement(UData_AbilityRequiredInfo* requiredInfo)
{
	// GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("USING FForward"));
	return true;
}

void AAbility_FForward::ActivateAbilityEffect(UData_AbilityRequiredInfo* requiredInfo)
{
	// do the effect
	if (requiredInfo->GetWorldPointer() != nullptr)
	{
		if (requiredInfo->GetPlayer() != nullptr)
		{
			CurrentWorld = requiredInfo->GetWorldPointer();
			MainPlayer = requiredInfo->GetPlayer();

			CurrentTimeDilation = CurrentTimeDilation * TimeDilationMultiplier;
			MainPlayer->CustomTimeDilation = CurrentTimeDilation;
			
			// if the bullet time niagara is still NOT spawned yet
			if (!MainPlayer->GetIsFForwardNiagaraSpawned())
			{
				MainPlayer->AttachFForwardNiagara();
				MainPlayer->SetIsFForwardNiagaraSpawned(true);
			}
			
			// run a timer to turn back the time dilation
			FFowardDuration = FFowardDuration * CurrentTimeDilation;
			CurrentWorld->GetTimerManager().SetTimer(FFowardTimer, this,
				&AAbility_FForward::ResetTimeDilation, FFowardDuration, true);

			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("piapiapia"));
		}

		//requiredInfo->GetEnemyTargetClass()->GetHitten(Damage->GetDamage());

		// Calculate the feedback -> override all calculation
		// freCost, freReward, cocost, coReward, moveSpeedRew, Xp
	}
}

void AAbility_FForward::ResetTimeDilation()
{
	if (IsValid(MainPlayer))
	{
		MainPlayer->CustomTimeDilation = NormalTimeDilation;
		CurrentTimeDilation = NormalTimeDilation;
		FFowardDuration = 5.0f;
		// if the bullet time niagara is spawned
		if (MainPlayer->GetIsFForwardNiagaraSpawned())
		{
			MainPlayer->DestroyFForwardNiagara();
			MainPlayer->SetIsFForwardNiagaraSpawned(false);
		}

		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("piupiupiu"));
	}
}