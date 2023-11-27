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
AEnemy9_Robot_Girl::AEnemy9_Robot_Girl()
{

}

// Called when the game starts or when spawned
void AEnemy9_Robot_Girl::BeginPlay()
{
	Super::BeginPlay();
	
	// Inicialize all values
	InitCharacHealth(100.0f);

	SetRarity(EEnemyRarity::ENormal);

	GeneralDistance = 2000.0f;

	BasicAttackDistance = 500.0f;
	AbilityOneDistance = 300.f;

	Ability1Duration = 1.0f;

}

void AEnemy9_Robot_Girl::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemy9_Robot_Girl::SpawnBasicAttackOrbs()
{
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	// only play one the animation, but fire multiple bullets
	Super::BasicAttack();

	FVector CenterPoint = GetActorLocation() + FVector(0.0f, 0.0f, AroundHeight);
	
	// Calculate the angle between each vector in radians
	const float AngleBetweenVectors = 2 * PI / AmountOfOrbs;

	// Generate vectors around the center point
	for (int32 i = 0; i < AmountOfOrbs; ++i)
	{
		float Angle = i * AngleBetweenVectors;
		FVector Direction = FVector(FMath::Cos(Angle), FMath::Sin(Angle), 0.0f);
		FVector OrbSpawnLocation = CenterPoint + Direction * OrbSpawnDistance;

		FVector OrbDestination = CenterPoint + Direction * OrbDestinationDistance;

		AWeapon_Bullet* Orb = GetWorld()->SpawnActor<AWeapon_Bullet>(Weapon_BulletClass,
			OrbSpawnLocation, GetActorRotation(), ActorSpawnParams);
		Orb->SetTargetLocation(OrbDestination);
		Orb->SetEnemyController(EnemyController);
		Orb->SetDamage(EnemyBaseDamage);
		Orb->SetbNormalFire(2000.0f, true);
	}
}

// create a portal which spawn infinitive bullet
void AEnemy9_Robot_Girl::SpawnAbilityOneOrbs()
{
	Super::Ability1();

	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FVector PortalSpawnLocation = GetActorLocation() + FVector(0.0f, 0.0f, PortalHeight);
	
	for (int i = 0; i < AmountOfPortalOrbs; ++i)
	{
		FVector PortalOrbDestination = CalculatePortalOrbDestination();

		AWeapon_Bullet* Orb = GetWorld()->SpawnActor<AWeapon_Bullet>(Weapon_BulletClass,
			PortalSpawnLocation, GetActorRotation(), ActorSpawnParams);
		Orb->SetTargetLocation(PortalOrbDestination);
		Orb->SetEnemyController(EnemyController);
		Orb->SetDamage(EnemyBaseDamage);
		Orb->SetbNormalFire(2000.0f, true);
	}
}

FVector AEnemy9_Robot_Girl::CalculatePortalOrbDestination()
{
	// calculate the destination
	FVector FireObjective = GetRandomNearbyLocationOfPlayer(DestinationOffSet);
	FVector FireDirection = (FireObjective - GetActorLocation());

	FVector FinalDestination = GetActorLocation() + FireDirection;

	DrawDebugSphere
	(
		GetWorld(), FinalDestination, 10.0f, 10, FColor::Green, false, 10.0f, 2, 10.0f
	);


	return FinalDestination;
}