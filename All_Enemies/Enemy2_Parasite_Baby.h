// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyClass.h"
#include "Enemy2_Parasite_Baby.generated.h"

UCLASS()
class LIMITLESS_API AEnemy2_Parasite_Baby : public AEnemyClass
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemy2_Parasite_Baby();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Basic Stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		TSubclassOf<class AEnemy2_Parasite_VenomGas> VenomGasClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		class AEnemy2_Parasite_VenomGas* VenomGas;


	// BasicAttack
	
	// Ability 1
	virtual void ExtraDiedAction() override;

public:	
	/*
	* BasicAttack -> bicho chase main, if it is close enough, deal damage
	* Ability 1 -> when it dead, create a cloud of venom at selflocation
	*/
	virtual void BasicAttack() override;
	virtual void Ability1() override;
};
