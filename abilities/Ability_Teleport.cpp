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
}

void AAbility_Teleport::ActivateAbilityEffect(UData_AbilityRequiredInfo* requiredInfo) {

	if (IsValid(requiredInfo->GetHitResult().GetActor())) {
		AWeapon_TeleportMarkClass = requiredInfo->GetPlayer()->GetTPMarkClass();
		if (IsValid(AWeapon_TeleportMarkClass)) {
			
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			AWeapon_TeleportMark* DeltaMark = requiredInfo->GetWorldPointer()
				->SpawnActor<AWeapon_TeleportMark>(AWeapon_TeleportMarkClass,
					requiredInfo->GetHitResult().Location,
					requiredInfo->GetPlayer()->GetActorRotation(), ActorSpawnParams);

			TeleportMarkList.Add(DeltaMark);
			
			FVector TPLocation = DeltaMark->GetActorLocation() + requiredInfo->GetPlayer()->GetMainHalfHeight();
			requiredInfo->GetPlayer()->TeleportTo(TPLocation, requiredInfo->GetPlayer()->GetActorRotation());
		}
	}
}