// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy15_Bat_1.h"
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

// Sets default values
AEnemy15_Bat_1::AEnemy15_Bat_1(){
}

void AEnemy15_Bat_1::BasicAttack() {
	Super::BasicAttack();
	UpdateExtraSpeed(1000.0f);
}

void AEnemy15_Bat_1::BasicAttackFinished() {
	Super::BasicAttackFinished();
	ResetExtraSpeed();

	ExtraDiedAction();
}

void AEnemy15_Bat_1::ExtraDiedAction() {
	Super::ExtraDiedAction();

	SelfExplode();
	Destroy();
}

void AEnemy15_Bat_1::SelfExplode() {
	DealExplotionDamage();
	SpawmExplodeNiagara();
}

void AEnemy15_Bat_1::DealExplotionDamage() {
	DealDamage2Overlapped();
}

FVector AEnemy15_Bat_1::GetPreAttackPosition() {
	return MainPosition;
}