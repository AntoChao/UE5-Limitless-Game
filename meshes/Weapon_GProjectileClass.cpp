// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon_GProjectileClass.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Components/BoxComponent.h"
#include "../Main.h"
#include "../MainController.h"
#include "../Enemies_Controller/AIEnemyClassController.h"
#include "Math/UnrealMathUtility.h"
#include "../All_Enemies/EnemyClass.h"

// Sets default values
AWeapon_GProjectileClass::AWeapon_GProjectileClass() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AWeapon_GProjectileClass::BeginPlay() {
	Super::BeginPlay();

	// fly object variables
	bStartingFire = false;
	bReCalculatingPath = false;
	bNormalFire = false;
	ChaseParameter = false;
	StartSplines = {};
	ReCalculateSplines = {};
	ReCalculateMaximum = 1;
	ReCalculateCounter = 0;
	StartSplineChosen = nullptr;
	ReCalculateSplineChosen = nullptr;
	TravelSpeed = 0.0f;
	ReFireDistance = 0.0f;
	SplineDistance = 0.0f;
}

// Called every frame
void AWeapon_GProjectileClass::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (bStartingFire) {
		StartFire(DeltaTime);
		UpdateLocationVariable();
		UpdateCollisionCompPosition();
	}
	else if (bReCalculatingPath) {
		ReCalculatePath(DeltaTime);
		UpdateLocationVariable();
		UpdateCollisionCompPosition();
	}
	else if (bNormalFire) {
		NormalFire(DeltaTime);

		// add recalculation logic after
		ReCalculateTrigger();

		UpdateLocationVariable();
		UpdateCollisionCompPosition();
	}
	else if (bGravityFire) {
		GravityFire(DeltaTime);
		
		UpdateLocationVariable();
		CalculateGravityForce();
		UpdateCollisionCompPosition();
	}

	IfReachLocation();
}

void AWeapon_GProjectileClass::CustomTickFunction() {
	GetWorldTimerManager().SetTimer(TickSimulatorTimer, this,
		&AWeapon_GProjectileClass::CustomTickFunction, TickSimulateTime, true);

}

// if the weapon is chase main type -> main should be set otherwise null
// The main is passed as a actor for simplicity, further use need a cast AMain type.
// *** May exist some offset location
void AWeapon_GProjectileClass::SetTarget(AActor* ATarget) {
	if (IsValid(this)) {
		RootLocation = GetActorLocation();
		CollisionLocation = GetActorLocation();

		if (IsValid(ATarget)) {
			Target = ATarget;
			TargetLocation = Target->GetActorLocation();

			AMain* mainTarget = Cast<AMain>(ATarget);
			if (IsValid(mainTarget)) {
				OwnByMain = false;
			}
			else {
				OwnByMain = true;
			}
		}
	}
}

void AWeapon_GProjectileClass::SetTargetLocation(FVector ATargetLocation) {
	RootLocation = GetActorLocation();
	CollisionLocation = GetActorLocation();
	TargetLocation = ATargetLocation;
}

// the DeltaTrans update is manually depending if it is spline or ...
void AWeapon_GProjectileClass::UpdateLocationVariable() {
	CollisionLocation = RootLocation + DeltaTrans.GetTranslation();

	if (IsValid(Target)) {
		if (ChaseParameter) {
			// constantly update player location
			TargetLocation = Target->GetActorLocation();
		}
		
		AttackDirection = TargetLocation - CollisionLocation;
		AttackDirection.Normalize();
	}
	
	// testing
	if (bGravityFire) {
		AttackDirection = TargetLocation - RootLocation;
		AttackDirection.Normalize();
	}

}

void AWeapon_GProjectileClass::SetbStartingFire(float ATravelSpeed, bool StartFireState) {
	// chose one of the start Spline
	int AmountOfStartSpline = StartSplines.Num();
	int Index = FMath::RandRange(0, AmountOfStartSpline - 1);

	StartSplineChosen = StartSplines[Index];

	// setting variables
	SplineDistance = 0.0f; // reset the distance
	TravelSpeed = ATravelSpeed;
	bStartingFire = StartFireState; // set this at the end, because it is ticking
}

void AWeapon_GProjectileClass::StartFire(float DeltaTime) {
	/*
	* 1 -> Using Random to select 1 start spline in its tset
	* 2 -> let the actor follor spline until it reach the end
	* 3 -> when reaching the end turns bStartingFire false
	*/

	SplineDistance = TravelSpeed * DeltaTime + SplineDistance;

	// get the transform along spline 
	DeltaTrans = StartSplineChosen->GetTransformAtDistanceAlongSpline (
		SplineDistance,
		ESplineCoordinateSpace::Local,
		false
	);

	// UpdateCollisionCompPosition();

	if (SplineDistance >= StartSplineChosen->GetSplineLength()) {
		bStartingFire = false;
		// when the start fire finish, it should travel to main
		bNormalFire = true;
	}
}

// NEED TO CHANGE THE LOGIC SOMEHOW, BECAUSE OTHERWISE IT NEVER FINISH THE CHASE
void AWeapon_GProjectileClass::ReCalculateTrigger() {
	// the weapon get in location
	// Check if the weapon is close enough to the player init location
	float DistanceToPlayer = FVector::Dist(TargetLocation, CollisionLocation);
	if (DistanceToPlayer < ReFireDistance) {
		SetbReCalculatingPath(true);
	}
}

void AWeapon_GProjectileClass::SetbReCalculatingPath(bool ReCalculateState) {
	// chose one of the start Spline
	int AmountOfStartSpline = ReCalculateSplines.Num();
	int Index = FMath::RandRange(0, AmountOfStartSpline - 1);

	ReCalculateSplineChosen = ReCalculateSplines[Index];
	
	// setting variables
	SplineDistance = 0.0f; // reset the distance
	bNormalFire = false;
	// Recalculate the target location
	RootLocation = TargetLocation;
	ReCalculateCounter += 1;

	// if the object already pass the recalculate max amount, destroy
	if (ReCalculateCounter > ReCalculateMaximum) {
		DieEffect();
	}

	// manually update target location as it is auto chase off
	if (IsValid(Target)) {
		TargetLocation = Target->GetActorLocation();
	}
	bReCalculatingPath = ReCalculateState; // set this at the end, because it is ticking
}

void AWeapon_GProjectileClass::ReCalculatePath(float DeltaTime) {
	/*
	* 1 -> Using Random to select 1 start spline in its tset
	* 2 -> let the actor follor spline until it reach the end
	* 3 -> when reaching the end turns bStartingFire false
	*/

	SplineDistance = TravelSpeed * DeltaTime + SplineDistance;

	// get the transform along spline 
	DeltaTrans = ReCalculateSplineChosen->GetTransformAtDistanceAlongSpline (
		SplineDistance,
		ESplineCoordinateSpace::Local,
		false
	);

	// UpdateCollisionCompPosition();
	
	if (SplineDistance >= ReCalculateSplineChosen->GetSplineLength()) {
		bReCalculatingPath = false;
		// when the start fire finish, it should travel to main
		bNormalFire = true;
	}
}

void AWeapon_GProjectileClass::SetbNormalFire(float ATravelSpeed, bool FireState) {
	// setting variables
	TravelSpeed = ATravelSpeed;

	AttackDirection = TargetLocation - RootLocation;
	AttackDirection.Normalize();

	bNormalFire = FireState; // set this at the end, because it is ticking
}

void AWeapon_GProjectileClass::NormalFire(float DeltaTime) {
	// Move the rocket towards the player
	DeltaTrans.AddToTranslation(AttackDirection * TravelSpeed * DeltaTime);
	DeltaTrans.SetRotation(AttackDirection.Rotation().Quaternion());
}
void AWeapon_GProjectileClass::SetbGravityFire(float ATravelSpeed, bool FireState) {
	// setting variables
	TravelSpeed = ATravelSpeed;

	AttackDirection = TargetLocation - RootLocation;
	AttackDirection.Normalize();

	// set this at the end, because it is ticking
	bGravityFire = FireState;
}

void AWeapon_GProjectileClass::GravityFire(float DeltaTime) {
	// Update the position and velocity using numerical integration (Euler's method)
	
	// normal attack direction calculation
	// AttackDirection = AttackDirection * GravityForce;

	// NO IDEA HOW TO DO
	DeltaTrans.AddToTranslation(AttackDirection * TravelSpeed * DeltaTime);
	DeltaTrans.SetRotation(AttackDirection.Rotation().Quaternion());
}

void AWeapon_GProjectileClass::CalculateGravityForce() {
	float DistanceToTarget = FVector::Dist(CollisionLocation, TargetLocation);
}

void AWeapon_GProjectileClass::UpdateCollisionCompPosition() {
	CollisionComp->SetWorldLocation(CollisionLocation);
	CollisionComp->SetWorldRotation(DeltaTrans.GetRotation());
}

// Does not even care the enemy parameter
void AWeapon_GProjectileClass::DoDamage(AActor* Actor) {
	
	if (IsValid(Actor)) {
		if (!OwnByMain) {
			UGameplayStatics::ApplyPointDamage(Actor, DamageComponent->GetDamage(), GetActorLocation(), MyHit, EnemyController, this, nullptr);
		}
		else {
			UGameplayStatics::ApplyPointDamage(Actor, DamageComponent->GetDamage(), GetActorLocation(), MyHit, MainController, this, nullptr);
		}
	}
	else if (IsValid(Target)) {
		if (!OwnByMain) {
			UGameplayStatics::ApplyPointDamage(Target, DamageComponent->GetDamage(), GetActorLocation(), MyHit, EnemyController, this, nullptr);
		}
		else {
			UGameplayStatics::ApplyPointDamage(Target, DamageComponent->GetDamage(), GetActorLocation(), MyHit, MainController, this, nullptr);
		}
	}
}

void AWeapon_GProjectileClass::IfReachLocation() {
	float DistanceToTargetLocation = FVector::Dist(TargetLocation, CollisionLocation);

	if (DistanceToTargetLocation < ReachOffSet) {
		ReachLocationEffect();
	}
}

void AWeapon_GProjectileClass::ReachLocationEffect() {
	Die();
}

void AWeapon_GProjectileClass::StopMoving() {
	bStartingFire = false;
	bReCalculatingPath = false;
	bNormalFire = false;
	bGravityFire = false;
}

FVector AWeapon_GProjectileClass::GetCollisionLocation() {
	return CollisionLocation;
}