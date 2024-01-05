// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyClass.h"
#include "Enemy4_Parasite_Ultimate.generated.h"

UCLASS()
class LIMITLESS_API AEnemy4_Parasite_Ultimate: public AEnemyClass
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemy4_Parasite_Ultimate();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void CustomTickFunction() override;

	//Basic Stats
	float MoveSpeed = 600.0f;

	FHitResult EnemyHit;
	
	FComponentQueryParams DefaultComponentQueryParams;
	FCollisionResponseParams DefaultResponseParam;

	
	// Ability 1 -> Charge and shot beam
	bool IsChargingBeam;
	FTimerHandle BeamChargingTimer;
	// WRONG -> SHOULD BE CHARGE BY ANIMATION
	float BeamChargingDuration; // the animation montage duration

	bool IsRelesingBeam;
	FTimerHandle BeamReleasingTimer;
	float BeamReleasingDuration;
	void ReleaseBeam();

	void BeamFinished();

	// Ability 2 ->	Jump to the location

public:	
	// Called every frame
	// virtual void Tick(float DeltaTime) override;

	// Receive Damage
	//virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	virtual void BasicAttack() override;
	virtual void Ability1() override;
	virtual void Ability2() override;

};
