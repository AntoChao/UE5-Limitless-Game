// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy22_Cultist.h"
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
AEnemy22_Cultist::AEnemy22_Cultist()
{

}


// basic attack called in animation
void AEnemy22_Cultist::SpawnCultist() {
	
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FVector TargetPosition = SelfPosition + SpawnXYOffset;

	// it automatically change the random location variable
	GenerateRandomPoint(SelfPosition, TargetPosition);

	RandomLocation = RandomLocation + SpawnHeightOffset;

	AEnemy22_Cultist* ACultist = GetWorld()->SpawnActor<AEnemy22_Cultist>(CultistClass,
		RandomLocation, GetActorRotation(), ActorSpawnParams);
}

void AEnemy22_Cultist::DealSelfDamage() {
	// Suicide, no need to pass an actual controller.
	/* NO WORKING CUZ EMEMIES ONLY RECEIVED MAIN DAMAGE
	UGameplayStatics::ApplyPointDamage(this, SelfDestoyDamage,
		GetActorLocation(), EnemyHit,
		nullptr, this, nullptr);*/

	ExtraDiedAction();
	Destroy();

}

void AEnemy22_Cultist::ExtraDiedAction() {
	SpawnSuicideExplotionNiagara();

	// need to set collision as around player
	DealDamage2Overlapped();

	// eliminate the health bar
	RemoveHealthBar();

	// reward main
	RewardMainCharacter();
}