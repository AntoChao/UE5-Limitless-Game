// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy28_Wasp.h"
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
AEnemy28_Wasp::AEnemy28_Wasp() {

}

void AEnemy28_Wasp::CustomTickFunction(){
	Super::CustomTickFunction();

	if (AttackDirection.Size() < GeneralDistance) {
		UGameplayStatics::ApplyPointDamage(MainPlayerTarget, EnemyBaseDamage,
			GetActorLocation(), EnemyHit, nullptr, this, nullptr);
	}
}





