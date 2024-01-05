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
}

bool AAbility_Sum_MomFoot::ShotTheLineTraceCheck(FVector HitLocation)
{
	FComponentQueryParams DefaultComponentQueryParams;
	FCollisionResponseParams DefaultResponseParam;

	FVector Start = HitLocation;
	FVector End = HitLocation + FVector(0.0f, 0.0f, MomFootHeight);

	GetWorld()->LineTraceSingleByChannel(LineTraceHit, HitLocation, End, ECC_Visibility, DefaultComponentQueryParams, DefaultResponseParam);

	return true;
}

void AAbility_Sum_MomFoot::ActivateAbilityEffect(UData_AbilityRequiredInfo* requiredInfo)
{
	// Ability Effect -> Spawn the grenade in hand and manipulate the character to throw and release
	SpawnFoot(requiredInfo);
}

void AAbility_Sum_MomFoot::SpawnFoot(UData_AbilityRequiredInfo* requiredInfo)
{
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	MomFoot = requiredInfo->GetWorldPointer()->SpawnActor<AWeapon_MomFoot>(requiredInfo->GetPlayer()->GetMomFootClass(),
			(requiredInfo->GetHitResult().Location + FVector(0.0f, 0.0f, 5000.0f)),
			FRotator(0.0f, 0.0f, 0.0f), ActorSpawnParams);

	MomFoot->SetTargetLocation(requiredInfo->GetHitResult().ImpactPoint);
	MomFoot->SetMainController(requiredInfo->GetPlayer()->GetMainController());
	MomFoot->SetDamage(CalculateGeneralDamage(requiredInfo));
	MomFoot->SetbNormalFire(5000.0f, true);
}