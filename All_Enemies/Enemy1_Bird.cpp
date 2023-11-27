// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy1_Bird.h"
#include "Engine/EngineTypes.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "../components/HealthComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"
#include "../meshes/Enemy1_Bird_WindSlash.h"
#include "../Main.h"

/*

*/
// Sets default values
AEnemy1_Bird::AEnemy1_Bird()
{

}

// Called when the game starts or when spawned
void AEnemy1_Bird::BeginPlay()
{
	Super::BeginPlay();
	
	// Inicialize all values
	InitCharacHealth(100.0f);
	
	SetRarity(EEnemyRarity::ENormal);

	GeneralDistance = 2000.0f;

	BasicAttackDistance = 1100.0f;
	AbilityOneDistance = 1100.0f;

	Ability1Duration = 1.0f;
	Ability2Duration = 1.0f;

	// GetCharacterMovement()->MaxWalkSpeed = FlySpeed;

}

void AEnemy1_Bird::CustomTickFunction()
{
	Super::CustomTickFunction();

	if (GetActorLocation().Z <= LimitHeight)
	{
		bFlyUp = true;
	}
	else
	{
		bFlyUp = false;
	}
}

bool AEnemy1_Bird::IsAbleToUseBasicAttack()
{
	return AttackDirection.Size() <= BasicAttackDistance;
}
bool AEnemy1_Bird::IsAbleToUseAbility1()
{
	return AttackDirection.Size() <= AbilityOneDistance;
}

/*
* Dash Attack, should create a collition or enable the collision around bird, and deal damage
*/
void AEnemy1_Bird::BasicAttack()
{
	Super::BasicAttack();
	UpdateExtraSpeed(1000.0f);
}

FVector AEnemy1_Bird::GetAttackFinishedPosition()
{
	FVector aux = AttackDirection * 2 + SelfPosition;
	//aux.Z = 105.5f;
	/*
	DrawDebugSphere
	(
		GetWorld(), aux, 10.0f, 10, FColor::Green, false, 10.0f, 2, 10.0f
	);*/
	return aux;
}

void AEnemy1_Bird::BasicAttackFinished()
{
	Super::BasicAttackFinished();
	ResetExtraSpeed();
}

void AEnemy1_Bird::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp,
	class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsAttacking)
	{
		if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
		{
			// if (OtherActor->GetClass()->IsChildOf(AAllCharactersClass::StaticClass()))
			if (OtherActor->IsA(AMain::StaticClass()))
			{
				// Apply damage
				ApplyDamageToMain(EnemyBaseDamage);
			}
		}
	}
}

void AEnemy1_Bird::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp,
	class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	// nothing
}

void AEnemy1_Bird::Ability1()
{
	Super::Ability1();
	
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	const FTransform orientation_socket_1 = Body->GetSocketTransform(Wind_Slash_Socket_1, ERelativeTransformSpace::RTS_World);
	const FTransform orientation_socket_2 = Body->GetSocketTransform(Wind_Slash_Socket_2, ERelativeTransformSpace::RTS_World);

	WindSlash1 = GetWorld()->SpawnActor<AEnemy1_Bird_WindSlash>(WindSlashClass,
		orientation_socket_1, ActorSpawnParams);
	WindSlash1->SetTarget(MainPlayerTarget);
	WindSlash1->SetEnemyController(EnemyController);
	WindSlash1->SetDamage(EnemyBaseDamage);
	WindSlash1->SetbNormalFire(1500.0f, true);

	WindSlash2 = GetWorld()->SpawnActor<AEnemy1_Bird_WindSlash>(WindSlashClass,
		orientation_socket_2, ActorSpawnParams);
	WindSlash1->SetTarget(MainPlayerTarget);
	WindSlash1->SetEnemyController(EnemyController);
	WindSlash1->SetDamage(EnemyBaseDamage);
	WindSlash1->SetbNormalFire(1500.0f, true);
}

void AEnemy1_Bird::Ability1Finished()
{
	Super::Ability1Finished();
}
