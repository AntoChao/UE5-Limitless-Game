// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyClass.h"
#include "Enemy13_Zombie.generated.h"

UCLASS()
class TRUEPROJECT2_API AEnemy13_Zombie : public AEnemyClass
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemy13_Zombie();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Basic Stats

	UPROPERTY(EditAnywhere, Category = "Enemies")
		TSubclassOf<class AMain> MainClass;

	FHitResult EnemyHit;
	
	FComponentQueryParams DefaultComponentQueryParams;
	FCollisionResponseParams DefaultResponseParam;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool IsJumping;
	UPROPERTY()
		float WalkSpeed;
	UPROPERTY()
		float JumpSpeed;

public:	
	virtual void BasicAttack() override;
	virtual void Ability1() override;
	virtual void Ability2() override;
	virtual bool IsAbleToUseAbility1() override;
	virtual bool IsAbleToUseAbility2() override;

	// Ability 1 -> Jump Attack
	virtual void Ability1Finished() override;

	// Ability 2-> X time Melee Continuos Attack
	
};
