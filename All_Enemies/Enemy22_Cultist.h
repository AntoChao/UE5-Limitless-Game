// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyClass.h"
#include "../meshes/Weapon_Shotgun.h"
#include "../meshes/Weapon_Bullet.h"
#include "Enemy22_Cultist.generated.h"

UCLASS()
class TRUEPROJECT2_API AEnemy22_Cultist : public AEnemyClass
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemy22_Cultist();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Basic Stats --> NO IDEA
	// Basic Attack -> spawn more cultist
	UFUNCTION(BlueprintCallable, Category = "BasicAttack")
		void SpawnCultist();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BasicAttack")
		FVector SpawnXYOffset = FVector(0.0f, 0.0f, 0.0f);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BasicAttack")
		FVector SpawnHeightOffset = FVector(0.0f, 0.0f, 64.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BasicAttack")
		TSubclassOf<class AEnemy22_Cultist> CultistClass;


	// Ability 1 -> Suicide and create explotion
	virtual void ExtraDiedAction() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability 1")
		float SelfDestoyDamage = 99999.0f;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "AbilityOne")
		void SpawnSuicideExplotionNiagara();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void BasicAttack() override;
	virtual void Ability1() override;
};
