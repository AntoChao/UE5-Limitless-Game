// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability_Teleport.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Engine/EngineTypes.h"
#include "Engine/Blueprint.h"
#include "DrawDebugHelpers.h"
#include "Math/Vector.h"
#include "../meshes/Weapon_TeleportMark.h"
#include "../AllCharactersClass.h"

// Sets default values
AAbility_Teleport::AAbility_Teleport(const class FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAbility_Teleport::BeginPlay()
{
	Super::BeginPlay();
}

bool AAbility_Teleport::AbilityRequirement(UData_AbilityRequiredInfo* requiredInfo)
{
	if (requiredInfo->GetPlayerFrenzy() >= FrenzyCost->GetFrenzy())
	{
		IsAbleToTP(requiredInfo);
		IsAbleToCreateMark(requiredInfo);

		return bAbleToTP || bAbleToCreateMark;
	}
	else
	{
		return false;
	}
}

/*
Run the mark list and get each one distance to player
*** NO NEED TO FIRE A TRACELINE, JUST GET THE POINT
Calculate the end point that has the same distance to player
*** Simulating a sphere check
Calculate the difference between the mark location and traceline end location
IF this difference is menor than a certain "radius"/ distance. return true, else false
*/
void AAbility_Teleport::IsAbleToTP(UData_AbilityRequiredInfo* requiredInfo)
{
	// fill the list MarkDistances
	FVector PlayerForwardVector = requiredInfo->GetPlayer()->GetForwardDirection();
	
	// should reset the mark distance list each time comparing
	MarkDistances = {};

	for (AWeapon_TeleportMark* MarkElement : TeleportMarkList)
	{
		FVector DeltaMarkLocation = MarkElement->GetActorLocation();
		FVector MarkDirection = DeltaMarkLocation - requiredInfo->GetPlayerLocation();
		float DeltaDistance = MarkDirection.Size();
		FVector DeltaEndLocation = requiredInfo->GetPlayerLocation() + (PlayerForwardVector * DeltaDistance);

		FVector DeltaDifference = DeltaMarkLocation - DeltaEndLocation;
		float DifferenceDistance = DeltaDifference.Size();

		MarkDistances.Add(DifferenceDistance);
	}

	// if there is no mark at all, set false
	// get the minimum distance mark
	if (TeleportMarkList.Num() == 0)
	{
		bAbleToTP = false;
	}
	else
	{
		MinDistance = MarkDistances[0];
		SelectedIndex = 0;
		for (int32 Index = 0; Index != MarkDistances.Num() - 1; ++Index)
		{
			if (MinDistance > MarkDistances[Index])
			{
				MinDistance = MarkDistances[Index];
				SelectedIndex = Index;
			}
		}

		// if this minmum distance mark is in view range, return T/F
		bAbleToTP = MinDistance <= ViewRange;

		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, TEXT("IS ABLE TO TP"));

	}
}

// There is charges and """FHit something""" -> No idea, may incorrect
void AAbility_Teleport::IsAbleToCreateMark(UData_AbilityRequiredInfo* requiredInfo)
{
	bAbleToCreateMark = MarkCharges != 0 && IsValid(requiredInfo->GetHitResult().GetActor());

	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, TEXT("IS ABLE TO CREAT TP MARK"));

}
bool AAbility_Teleport::GetIsAbleToTP()
{
	return bAbleToTP;
}
bool AAbility_Teleport::GetIsAbleToPutMark()
{
	return bAbleToCreateMark;
}

/*  ActivateAbilityEffect has 3 process
*	Customize ability stats
*	Do the effect
*	Calculate feedback in order to return -> override all calculution base on ability
*/
void AAbility_Teleport::ActivateAbilityEffect(UData_AbilityRequiredInfo* requiredInfo)
{
	AWeapon_TeleportMarkClass = requiredInfo->GetPlayer()->GetTPMarkClass();

	// Ability Effect -> Spawn the grenade in hand and manipulate the character to throw and release
	// should not have any more possibilities, other wise unable
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("1"));
	if (bAbleToTP)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("2"));
		TP(requiredInfo);
	}
	else if (bAbleToCreateMark)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("3"));
		CreateNewTPMark(requiredInfo);
	}

	// Calculate the feedback -> override all calculation -> the calculation is done after receive the decision
	// freCost, freReward, cocost, coReward, moveSpeedRew, Xp
}

/*
TP -> set player location on selected mark
eliminate the selected mark and mark count ++ 1
*/
void AAbility_Teleport::TP(UData_AbilityRequiredInfo* requiredInfo)
{
	// just in case, double check the tp requirement
	if (!TeleportMarkList.Num() == 0)
	{
		// RAISE ERROR
		// get the mark selected
		MarkSelected = TeleportMarkList[SelectedIndex];

		// can use setactorlocation or teleportTo
		requiredInfo->GetPlayer()->TeleportTo(MarkSelected->GetActorLocation(), requiredInfo->GetPlayer()->GetActorRotation());

		// remove the mark from the list
		EliminateTPMark(MarkSelected);
		MarkSelected->Destroy();

		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("TPING"));
	}
	

}

void AAbility_Teleport::CreateNewTPMark(UData_AbilityRequiredInfo* requiredInfo)
{
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;


	AWeapon_TeleportMark* DeltaMark = requiredInfo->GetWorldPointer()->
		SpawnActor<AWeapon_TeleportMark>(AWeapon_TeleportMarkClass,
			requiredInfo->GetHitResult().Location, 
			requiredInfo->GetPlayer()->GetActorRotation(), ActorSpawnParams);

	TeleportMarkList.Add(DeltaMark);

	// minus mark charges
	MarkCharges -= 1;

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("CREATING MARK"));

}
void AAbility_Teleport::EliminateTPMark(AWeapon_TeleportMark* AMark)
{
	TeleportMarkList.Remove(AMark);
	MarkCharges += 1;

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("ELIMINATE MARK"));

}