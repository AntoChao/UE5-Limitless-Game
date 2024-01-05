// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyClass.h"
#include "Enemy3_Parasite_Rookie.generated.h"

UCLASS()
class LIMITLESS_API AEnemy3_Parasite_Rookie : public AEnemyClass
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemy3_Parasite_Rookie();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void CustomTickFunction() override;

	//Basic Stats
	FHitResult EnemyHit;
	
	FComponentQueryParams DefaultComponentQueryParams;
	FCollisionResponseParams DefaultResponseParam;
	
	//Basic Stats
	// venom gas
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		TSubclassOf<class AEnemy2_Parasite_VenomGas> VenomGasClass;

	// baby parasite
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Baby")
		int AmountOfBaby2Spawn = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Baby")
		TSubclassOf<class AEnemy2_Parasite_Baby> Parasite_BabyClass;

	// BasicAttack

	// Ability 1
	virtual void ExtraDiedAction() override;

public:	
	virtual void BasicAttack() override;
	virtual void Ability1() override;

};
