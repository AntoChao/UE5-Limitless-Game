// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy9_Robot_Girl.h"
#include "Engine/EngineTypes.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "../components/HealthComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"
#include "../Main.h"

/*

*/
// Sets default values
AEnemy9_Robot_Girl::AEnemy9_Robot_Girl(){

}

void AEnemy9_Robot_Girl::SpawnBasicAttackOrbs() {
	Super::BasicAttack();

	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FVector CenterPoint = GetActorLocation() + FVector(0.0f, 0.0f, AroundHeight);
	
	// Calculate the angle between each vector in radians
	const float AngleBetweenVectors = 2 * PI / AmountOfOrbs;

	// Generate vectors around the center point
	for (int32 i = 0; i < AmountOfOrbs; ++i) {
		float Angle = i * AngleBetweenVectors;
		FVector Direction = FVector(FMath::Cos(Angle), FMath::Sin(Angle), 0.0f);
		FVector OrbSpawnLocation = CenterPoint + Direction * OrbSpawnDistance;

		FVector OrbDestination = CenterPoint + Direction * OrbDestinationDistance;

		AWeapon_Bullet* Orb = GetWorld()->SpawnActor<AWeapon_Bullet>(Weapon_BulletClass,
			OrbSpawnLocation, GetActorRotation(), ActorSpawnParams);

		if (IsValid(Orb)) {
			Orb->SetTargetLocation(OrbDestination);
			Orb->SetEnemyController(EnemyController);
			Orb->SetDamage(EnemyBaseDamage);
			Orb->SetbNormalFire(500.0f, true);
		}
	}
}

// create a portal which spawn infinitive bullet
void AEnemy9_Robot_Girl::SpawnAbilityOneOrbs() {
	Super::Ability1();

	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FVector PortalSpawnLocation = GetActorLocation() + FVector(0.0f, 0.0f, PortalHeight);
	
	for (int i = 0; i < AmountOfPortalOrbs; ++i) {
		FVector PortalOrbDestination = CalculatePortalOrbDestination();

		AWeapon_Bullet* Orb = GetWorld()->SpawnActor<AWeapon_Bullet>(Weapon_BulletClass,
			PortalSpawnLocation, GetActorRotation(), ActorSpawnParams);

		if (IsValid(Orb)) {
			Orb->SetTargetLocation(PortalOrbDestination);
			Orb->SetEnemyController(EnemyController);
			Orb->SetDamage(EnemyBaseDamage);
			Orb->SetbNormalFire(1000.0f, true);
		}
	}
}

FVector AEnemy9_Robot_Girl::CalculatePortalOrbDestination() {
	// calculate the destination
	FVector FireObjective = GetRandomNearbyLocationOfPlayer(DestinationOffSet);
	FVector FireDirection = (FireObjective - GetActorLocation());

	FVector FinalDestination = GetActorLocation() + FireDirection;

	return FinalDestination;
}