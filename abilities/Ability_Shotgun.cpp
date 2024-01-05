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
	:Super(ObjectInitializer) {
}

void AAbility_Shotgun::ActivateAbilityEffect(UData_AbilityRequiredInfo* requiredInfo) {
    FVector EnemyDirection = requiredInfo->GetHitResult().TraceEnd;
    FVector ShotgunLocation = requiredInfo->GetPlayer()->GetActorLocation();

    TArray<FVector> SpreadDirections = CalculateSpreadDirections(ShotgunLocation,
        EnemyDirection);
    
    FHitResult HitResult;
    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(this); // Ignore the shotgun actor
    CollisionParams.AddIgnoredActor(requiredInfo->GetPlayer());

    // Fire traces for each spread direction
    for (FVector Direction : SpreadDirections) {
        FVector EndPoint = ShotgunLocation + Direction * MaxDistance;

        bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult,
            ShotgunLocation, EndPoint, ECC_Visibility, CollisionParams);

        // Draw debug line for visualization
        if (bHit) {
            if (IsValid(HitResult.GetActor())) {
                AEnemyClass* EnemyDelta = Cast<AEnemyClass>(HitResult.GetActor());
                if (IsValid(EnemyDelta)) {
                    ApplyDamageToEnemy(EnemyDelta, CalculateShotgunDamage(HitResult, requiredInfo), requiredInfo);
                }
            }
        }
    }
}

TArray<FVector> AAbility_Shotgun::CalculateSpreadDirections(FVector ShotgunLocation, FVector DestinationLocation) {
    TArray<FVector> SpreadDirections;

    FVector ShotgunToDestination = (DestinationLocation - ShotgunLocation).GetSafeNormal();
    FVector ShotgunForward = FVector::ForwardVector; // Define your shotgun's forward vector

    for (int32 i = 0; i < NumberOfTraces; ++i) {
        // Randomly deviate from the shotgun's forward direction within the spread angle
        FRotator RandomRotation = FRotator(FMath::RandRange(-ConeAngle, ConeAngle), FMath::RandRange(-ConeAngle, ConeAngle), 0.0f);
        FVector SpreadDirection = RandomRotation.RotateVector(ShotgunToDestination);

        SpreadDirections.Add(SpreadDirection);
    }

    return SpreadDirections;
}

float AAbility_Shotgun::CalculateShotgunDamage(FHitResult HitResult,
    UData_AbilityRequiredInfo* requiredInfo) {

    float Distance = HitResult.Distance;
    float GeneralDamage = CalculateGeneralDamage(requiredInfo);

    float DamageDealed = FMath::Lerp(GeneralDamage, 0.0f, Distance / MaxDistance);

    if (DamageDealed >= 0) {
        return DamageDealed;
    }
    else {
        return 0;
    }
}
